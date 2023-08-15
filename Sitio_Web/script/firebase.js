  // Import the functions you need from the SDKs you need
  import { initializeApp } from "https://www.gstatic.com/firebasejs/10.1.0/firebase-app.js";
  // TODO: Add SDKs for Firebase products that you want to use
  // https://firebase.google.com/docs/web/setup#available-libraries

  // Your web app's Firebase configuration
  const firebaseConfig = {
    apiKey: "AIzaSyCLZ0TXHysYl7vusOEvMc-hXmLv2PKnC9c",
    authDomain: "smartparking-612d8.firebaseapp.com",
    databaseURL: "https://smartparking-612d8-default-rtdb.firebaseio.com",
    projectId: "smartparking-612d8",
    storageBucket: "smartparking-612d8.appspot.com",
    messagingSenderId: "660267338598",
    appId: "1:660267338598:web:33b06703f6bfb021bc16a7"
  };

  // Initialize Firebase
  export const app = initializeApp(firebaseConfig);