<script>
// Simulate a call to Dropbox or other service that can
// return an image as an ArrayBuffer.
var xhr = new XMLHttpRequest();

// Use JSFiddle logo as a sample image to avoid complicating
// this example with cross-domain issues.
xhr.open( "GET", "http://fiddle.jshell.net/img/logo.png", true );

// Ask for the result as an ArrayBuffer.
xhr.responseType = "arraybuffer";

xhr.onload = function( e ) {
    // Obtain a blob: URL for the image data.
    var arrayBufferView = new Uint8Array( this.response );
    var blob = new Blob( [ arrayBufferView ], { type: "image/jpeg" } );
    var urlCreator = window.URL || window.webkitURL;
    var imageUrl = urlCreator.createObjectURL( blob );
    var img = document.querySelector( "#photo" );
    img.src = imageUrl;
};

xhr.send();

// ----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Please note this method does not convert a PNG image into a JPG. In order to do so, you have to put the image in a <canvas> and export it using .toDataURI or .toBlob (not always possibile, as the image must have the same origin) using 'image/jpeg' as the output format.

I know this isn't the reason of this gist, just warning other passers-by who may get confused.

</script>
