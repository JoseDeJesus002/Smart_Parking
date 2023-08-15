import { onAuthStateChanged } from "https://www.gstatic.com/firebasejs/10.1.0/firebase-auth.js";
import { auth } from "./firebase.js";

// import './form-register.js';
import "./logout.js";
import { loginCheck } from "./loginCheck.js";

onAuthStateChanged(auth, async (user) => {
  loginCheck(user);
  // if(user){
  // }else{
  //     loginCheck(user);
  // }
});
