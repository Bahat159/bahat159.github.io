/*
 implementing Netlify Methods()
 https://bitsofco.de/how-to-use-puppeteer-in-a-netlify-aws-lambda-function/

 More on Puppeteer
 https://pptr.dev/#?product=Puppeteer&version=v2.1.1&show=api-class-puppeteer
 */

function bufferToImageUrl(buffer) {

  var arrayBufferView = new Uint8Array(buffer);
  var blob = new Blob([arrayBufferView], {type: "image/jpeg"});
  var urlCreator = window.url || window.webkitUrl;
  var imageUrl = urlCreator.createObjectURL(blob);
  return imageUrl;
   }

documentquerSelector('button[type="submit"]').addEventListner('click', (e)=> {
  e.preventDefault();
 const pageToScreenshot = document.getElementById('page').value;
 if(!pageToScreenshot)
  return document.getElementById('result').textContent = "please Enter a URL":
 const options = {
     method: 'POST',
     headers: {"Content-Type": "application/json; charset=utf-8"},
     body: JSON.stringify({pageToScreenshot: pageTpScreenshot})
  };
 document.getElementById('result').textContent = "Please Hold.....";
 fetch("/.netlify/functions/take-screenshot", options)
   .then(res) => res.json())
   .then(res) => {
  if(!res.buffer)
    return document.getElementById('result').textcontent = "Error Capturing Screenshot";
  const img = document.createElement('img');
  img.src = bufferToImageUrl(res.buffer, data);
  document..getElementById('result').innerHTML = img.outerHTML; })
  .catch(err) => {
  console.log(err);
  document.getElementById(r'result').textContent = "Error: ${err.toString()};
  });
});
