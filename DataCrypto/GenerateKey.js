// GenerateKeyPair()
//AES

(() => {

  /*
  Store the calculated ciphertext and IV here, so we can decrypt the message later.
  */
  let ciphertext;
  let iv;

  /*
  Fetch the contents of the "message" textbox, and encode it
  in a form we can use for the encrypt operation.
  */
  function getMessageEncoding() {
    const messageBox = document.querySelector("#aes-gcm-message");
    let message = messageBox.value;
    let enc = new TextEncoder();
    return enc.encode(message);
  }

  /*
  Get the encoded message, encrypt it and display a representation
  of the ciphertext in the "Ciphertext" element.
  */
  async function encryptMessage(key) {
    let encoded = getMessageEncoding();
    // The iv must never be reused with a given key.
    iv = window.crypto.getRandomValues(new Uint8Array(12));
    ciphertext = await window.crypto.subtle.encrypt(
      {
        name: "AES-GCM",
        iv: iv
      },
      key,
      encoded
    );

    let buffer = new Uint8Array(ciphertext, 0, 5);
    const ciphertextValue = document.querySelector(".aes-gcm .ciphertext-value");
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
        name: "AES-GCM",
        iv: iv
      },
      key,
      ciphertext
    );

    let dec = new TextDecoder();
    const decryptedValue = document.querySelector(".aes-gcm .decrypted-value");
    decryptedValue.classList.add('fade-in');
    decryptedValue.addEventListener('animationend', () => {
      decryptedValue.classList.remove('fade-in');
    });
    decryptedValue.textContent = dec.decode(decrypted);
  }

  /*
  Generate an encryption key, then set up event listeners
  on the "Encrypt" and "Decrypt" buttons.
  */
  window.crypto.subtle.generateKey(
    {
        name: "AES-GCM",
        length: 256,
    },
    true,
    ["encrypt", "decrypt"]
  ).then((key) => {
    const encryptButton = document.querySelector(".aes-gcm .encrypt-button");
    encryptButton.addEventListener("click", () => {
      encryptMessage(key);
    });

    const decryptButton = document.querySelector(".aes-gcm .decrypt-button");
    decryptButton.addEventListener("click", () => {
      decryptMessage(key);
    });
  });

})();


//HMAC Key Generation

(() => {

  /*
  Store the calculated signature here, so we can verify it later.
  */
  let signature;

  /*
  Fetch the contents of the "message" textbox, and encode it
  in a form we can use for sign operation.
  */
  function getMessageEncoding() {
    const messageBox = document.querySelector("#hmac-message");
    let message = messageBox.value;
    let enc = new TextEncoder();
    return enc.encode(message);
  }

  /*
  Get the encoded message-to-sign, sign it and display a representation
  of the first part of it in the "signature" element.
  */
  async function signMessage(key) {
    const signatureValue = document.querySelector(".hmac .signature-value");
    signatureValue.classList.remove("valid", "invalid");

    let encoded = getMessageEncoding();
    signature = await window.crypto.subtle.sign(
      "HMAC",
      key,
      encoded
    );

    signatureValue.classList.add('fade-in');
    signatureValue.addEventListener('animationend', () => {
      signatureValue.classList.remove('fade-in');
    });
    let buffer = new Uint8Array(signature, 0, 5);
    signatureValue.textContent = `${buffer}...[${signature.byteLength} bytes total]`;
  }

  /*
  Fetch the encoded message-to-sign and verify it against the stored signature.
  * If it checks out, set the "valid" class on the signature.
  * Otherwise set the "invalid" class.
  */
  async function verifyMessage(key) {
    const signatureValue = document.querySelector(".hmac .signature-value");
    signatureValue.classList.remove("valid", "invalid");

    let encoded = getMessageEncoding();
    let result = await window.crypto.subtle.verify(
      "HMAC",
      key,
      signature,
      encoded
    );

    signatureValue.classList.add(result ? "valid" : "invalid");
  }

  /*
  Generate a sign/verify key, then set up event listeners
  on the "Sign" and "Verify" buttons.
  */
  window.crypto.subtle.generateKey(
    {
      name: "HMAC",
      hash: {name: "SHA-512"}
    },
    true,
    ["sign", "verify"]
  ).then((key) => {
    const signButton = document.querySelector(".hmac .sign-button");
    signButton.addEventListener("click", () => {
      signMessage(key);
    });

    const verifyButton = document.querySelector(".hmac .verify-button");
    verifyButton.addEventListener("click", () => {
      verifyMessage(key);
    });
  });

})();

//ELLIPTIC cURVE key Generation

(() => {

  /*
  Store the calculated signature here, so we can verify it later.
  */
  let signature;

  /*
  Fetch the contents of the "message" textbox, and encode it
  in a form we can use for sign operation.
  */
  function getMessageEncoding() {
    const messageBox = document.querySelector("#ecdsa-message");
    let message = messageBox.value;
    let enc = new TextEncoder();
    return enc.encode(message);
  }

  /*
  Get the encoded message-to-sign, sign it and display a representation
  of the first part of it in the "signature" element.
  */
  async function signMessage(privateKey) {
    const signatureValue = document.querySelector(".ecdsa .signature-value");
    signatureValue.classList.remove("valid", "invalid");

    let encoded = getMessageEncoding();
    signature = await window.crypto.subtle.sign(
      {
        name: "ECDSA",
        hash: {name: "SHA-384"},
      },
      privateKey,
      encoded
    );

    signatureValue.classList.add('fade-in');
    signatureValue.addEventListener('animationend', () => {
      signatureValue.classList.remove('fade-in');
    });
    let buffer = new Uint8Array(signature, 0, 5);
    signatureValue.textContent = `${buffer}...[${signature.byteLength} bytes total]`;
  }

  /*
  Fetch the encoded message-to-sign and verify it against the stored signature.
  * If it checks out, set the "valid" class on the signature.
  * Otherwise set the "invalid" class.
  */
  async function verifyMessage(publicKey) {
    const signatureValue = document.querySelector(".ecdsa .signature-value");
    signatureValue.classList.remove("valid", "invalid");

    let encoded = getMessageEncoding();
    let result = await window.crypto.subtle.verify(
      {
        name: "ECDSA",
        hash: {name: "SHA-384"},
      },
      publicKey,
      signature,
      encoded
    );

    signatureValue.classList.add(result ? "valid" : "invalid");
  }

  /*
  Generate a sign/verify key, then set up event listeners
  on the "Sign" and "Verify" buttons.
  */
  window.crypto.subtle.generateKey(
    {
      name: "ECDSA",
      namedCurve: "P-384"
    },
    true,
    ["sign", "verify"]
  ).then((keyPair) => {
    const signButton = document.querySelector(".ecdsa .sign-button");
    signButton.addEventListener("click", () => {
      signMessage(keyPair.privateKey);
    });

    const verifyButton = document.querySelector(".ecdsa .verify-button");
    verifyButton.addEventListener("click", () => {
      verifyMessage(keyPair.publicKey);
    });
  });

})();

//RSA-OAEP KEy Generation

(() => {

  /*
  Store the calculated ciphertext here, so we can decrypt the message later.
  */
  let ciphertext;

  /*
  Fetch the contents of the "message" textbox, and encode it
  in a form we can use for the encrypt operation.
  */
  function getMessageEncoding() {
    const messageBox = document.querySelector("#rsa-oaep-message");
    let message = messageBox.value;
    let enc = new TextEncoder();
    return enc.encode(message);
  }

  /*
  Get the encoded message, encrypt it and display a representation
  of the ciphertext in the "Ciphertext" element.
  */
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

  /*
  Generate an encryption key pair, then set up event listeners
  on the "Encrypt" and "Decrypt" buttons.
  */
  window.crypto.subtle.generateKey(
    {
    name: "RSA-OAEP",
    // Consider using a 4096-bit key for systems that require long-term security
    modulusLength: 2048,
    publicExponent: new Uint8Array([1, 0, 1]),
    hash: "SHA-256",
    },
    true,
    ["encrypt", "decrypt"]
  ).then((keyPair) => {
    const encryptButton = document.querySelector(".rsa-oaep .encrypt-button");
    encryptButton.addEventListener("click", () => {
      (keyPair.publicKey);
    });

    const decryptButton = document.querySelector(".rsa-oaep .decrypt-button");
    decryptButton.addEventListener("click", () => {
      decryptMessage(keyPair.privateKey);
    });
  });

})();
