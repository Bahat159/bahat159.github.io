document.addEventListener('DOMContentLoaded', () => {
  const themeSelector = document.getElementById('theme-selector');
  if (!themeSelector) return;
  // Read preference from storage or fallback to device system settings
  const currentTheme = sessionStorage.getItem('theme') || 
    (window.matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light');
  // Sync current state onto DOM element tree and input selection value
  document.documentElement.setAttribute('data-theme', currentTheme);
  themeSelector.value = currentTheme;
  // Dynamic tracking handler on select options changes
  themeSelector.addEventListener('change', (event) => {
    const selectedTheme = event.target.value;
    document.documentElement.setAttribute('data-theme', selectedTheme);
    sessionStorage.setItem('theme', selectedTheme);
  });
});
