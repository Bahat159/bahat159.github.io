#include <windows.h>
#include <windowsx.h>
#include <wchar.h>
#include "FirstWindowApp.h"
#include <memory>
#include <list>
#pragma once

/// define numeric identifiers for the table and for the application commands. 
/// These values are arbitrary

#define IDR_ACCEL1                      101
#define ID_TOGGLE_MODE                40002
#define ID_DRAW_MODE                  40003
#define ID_SELECT_MODE				  40004


struct MyEllipse
{
	D2D1_ELLIPSE    ellipse;
	D2D1_COLOR_F    color;

	void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush)
	{
		pBrush->SetColor(color);
		pRT->FillEllipse(ellipse, pBrush);
		pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		pRT->DrawEllipse(ellipse, pBrush, 1.0f);
	}

	BOOL HitTest(float x, float y)
	{
		const float a = ellipse.radiusX;
		const float b = ellipse.radiusY;
		const float x1 = x - ellipse.point.x;
		const float y1 = y - ellipse.point.y;
		const float d = ((x1 * x1) / (a * a)) + ((y1 * y1) / (b * b));
		return d <= 1.0f;
	}
};

std::list<std::shared_ptr<MyEllipse>>             ellipses;
std::list<std::shared_ptr<MyEllipse>>::iterator   selection;

std::shared_ptr<MyEllipse> Selection()
{
	if (selection == ellipses.end())
	{
		return nullptr;
	}
	else
	{
		return (*selection);
	}
}

void    ClearSelection() { selection = ellipses.end(); }


class DPIScale {
	static float scaleX;
	static float scaleY;
public:
	static void Initialize(ID2D1Factory* pFactory) {
		FLOAT dpiX, dpiY;
		pFactory->GetDesktopDpi(&dpiX, &dpiY);
		scaleX = dpiX / 96.0f;
		scaleY = dpiY / 96.0f;
	}
	template <typename T>
	static D2D1_POINT_2F PixelsToDips(T x, T y)
	{
		return D2D1::Point2F(static_cast<float>(x) / scaleX, static_cast<float>(y) / scaleY);
	}

};

float DPIScale::scaleX = 1.0f;
float DPIScale::scaleY = 1.0f;

class MouseTrackEvents : public BaseWindow<MainWindow>  {
	bool m_bMouseTracking;
public:
	MouseTrackEvents() : m_bMouseTracking(false) {}
	void OmMouseMove(HWND hwnd) {
		if (!m_bMouseTracking) {
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_HOVER | TME_LEAVE;
			tme.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent(&tme);
			m_bMouseTracking = true;
		}
	}
	void Reset(HWND hwnd) {
		m_bMouseTracking = false;
	}
	UINT GetMouseHoverTime() {
		UINT msec;
		if (SystemParametersInfo(SPI_GETMOUSEHOVERTIME, 0, &msec, 0)) {
			return msec;
		}
		else {
			return 0;
		}
	}
	BOOL IsMouseWheelPresent(){
		return (GetSystemMetrics(SM_MOUSEWHEELPRESENT) != 0);
	}
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

};

LRESULT MouseTrackEvents::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

class MouseMovement : public BaseWindow<MainWindow>
{
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;
	D2D1_ELLIPSE            ellipse;
	D2D1_POINT_2F           ptMouse;

	void	CalculateLayout() {};
	void    OnLButtonDown(int pixelX, int pixelY, DWORD flags);
	void    OnLButtonUp();
	void    OnMouseMove(int pixelX, int pixelY, DWORD flags);
	void	ConfineCursorToScreen();
public:
	MouseMovement() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL), ellipse(D2D1::Ellipse(D2D1::Point2F(), 0, 0)), ptMouse(D2D1::Point2F()){}
	PCWSTR ClassName() const {
		return L"Circle Window Class";
	}
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

void MouseMovement::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{
	SetCapture(m_hwnd);
	ellipse.point = ptMouse = DPIScale::PixelsToDips(pixelX, pixelY);
	ellipse.radiusX = ellipse.radiusY = 1.0f;
	InvalidateRect(m_hwnd, NULL, FALSE);
}

void MouseMovement::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
	if (flags & MK_LBUTTON)
	{
		const D2D1_POINT_2F dips = DPIScale::PixelsToDips(pixelX, pixelY);

		const float width = (dips.x - ptMouse.x) / 2;
		const float height = (dips.y - ptMouse.y) / 2;
		const float x1 = ptMouse.x + width;
		const float y1 = ptMouse.y + height;

		ellipse = D2D1::Ellipse(D2D1::Point2F(x1, y1), width, height);

		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void MouseMovement::OnLButtonUp()
{
	ReleaseCapture();
}

void MouseMovement::ConfineCursorToScreen() {
	RECT rc;
	GetClientRect(m_hwnd, &rc);

	// Convert the client area to screen coordinates.
	POINT pt = { rc.left, rc.top };
	POINT pt2 = { rc.right, rc.bottom };
	ClientToScreen(m_hwnd, &pt);
	ClientToScreen(m_hwnd, &pt2);
	SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

	// Confine the cursor.
	ClipCursor(&rc);
}


LRESULT MouseMovement::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
			return -1;
		}
		DPIScale::Initialize(pFactory);
		return 0;
	case WM_LBUTTONDOWN:
		OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;
	case WM_LBUTTONUP:
		OnLButtonUp();
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
