( () => {

  function getMessageEncoding() {
    const messageBox = document.querySelector("#rsa-oaep-message");
    let message = messageBox.value;
    let enc = new TextEncoder();
    return enc.encode(message);
  }

 function encryptMessage(publickey) {
  let encoded = getMessageEncoding();
  return window.crypto.subtl.encrypt(
   { 
    name: "RSA-OAEP"
       }, 
      publickey, encoded
      );
    let buffer = new Uint8Array(ciphertext, 0, 5);
    const ciphertextValue = document.querySelector(".rsa-oaep .ciphertext-value");
    ciphertextValue.classList.add('fade-in');
    ciphertextValue.addEventListener('animationend', () => {
      ciphertextValue.classList.remove('fade-in');
    });
    ciphertextValue.textContent = `${buffer}...[${ciphertext.byteLength} bytes total]`;
  }

 
//const result = crypto.subtle.generateKey(algorithm, extractable, keyUsages);
//RSA Key Pair genetation

let keyPair = window.crypto.subtle.generateKey(
  {
    name: "RSA-OAEP",
    modulusLength: 4096,
    publicExponent: new Uint8Array([1, 0, 1]),
    hash: "SHA-256"
  },
  true,
  ["encrypt", "decrypt"]
);

//Elliptic Curve Key Pair generation
let keyPair = window.crypto.subtle.generateKey(
  {
    name: "ECDSA",
    namedCurve: "P-384"
  },
  true,
  ["sign", "verify"]
);

//HMAC Key generation
let key = window.crypto.subtle.generateKey(
  {
    name: "HMAC",
    hash: {name: "SHA-512"}
  },
  true,
  ["sign", "verify"]
);

//AES Key Generation

let key = window.crypto.subtle.generateKey(
  {
    name: "AES-GCM",
    length: 256
  },
  true,
  ["encrypt", "decrypt"]
);


// decrypt()

 let ciphertext;

 async function encryptMessage(key) {
    let encoded = getMessageEncoding();
    ciphertext = await window.crypto.subtle.encrypt(
      {
        name: "RSA-OAEP"
      },
      key,
      encoded
    );

    let buffer = new Uint8Array(ciphertext, 0, 5);
    const ciphertextValue = document.querySelector(".rsa-oaep .ciphertext-value");
    ciphertextValue.classList.add('fade-in');
    ciphertextValue.addEventListener('animationend', () => {
      ciphertextValue.classList.remove('fade-in');
    });
    ciphertextValue.textContent = `${buffer}...[${ciphertext.byteLength} bytes total]`;
  }

  /*
  Fetch the ciphertext and decrypt it.
  Write the decrypted message into the "Decrypted" box.
  */
  async function decryptMessage(key) {
    let decrypted = await window.crypto.subtle.decrypt(
      {
        name: "RSA-OAEP"
      },
      key,
      ciphertext
    );

    let dec = new TextDecoder();
    const decryptedValue = document.querySelector(".rsa-oaep .decrypted-value");
    decryptedValue.classList.add('fade-in');
    decryptedValue.addEventListener('animationend', () => {
      decryptedValue.classList.remove('fade-in');
    });
    decryptedValue.textContent = dec.decode(decrypted);
  }


//crypto.sign()

async function signMessage(privateKey) {
    const signatureValue = document.querySelector(".rsassa-pkcs1 .signature-value");
    signatureValue.classList.remove("valid", "invalid");

    let encoded = getMessageEncoding();
    signature = await window.crypto.subtle.sign(
      "RSASSA-PKCS1-v1_5",
      privateKey,
      encoded
    );
