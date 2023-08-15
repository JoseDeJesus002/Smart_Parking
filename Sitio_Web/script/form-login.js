// importar función para crear usuario
import { signInWithEmailAndPassword } from "https://www.gstatic.com/firebasejs/10.1.0/firebase-auth.js";
// importar firebase
import { auth } from "./firebase.js";
// importar función para mostrar mensajes
import { showMessages } from "./showMessages.js";

const singInForm = document.querySelector("#login");

singInForm.addEventListener("submit", async (e) => {
  e.preventDefault();

  const email = singInForm["email-login"].value;
  const password = singInForm["password-login"].value;

  try {
    const credentials = await signInWithEmailAndPassword(auth, email, password);

    showMessages("Inicio de sesion correcto...", "success");
    setTimeout(function () {
      window.location.href = "index.html";
    }, 2000);
  } catch (error) {
    if (error.code === "auth/user-not-found") {
      showMessages("Usuario no encontrado", "error");
    }
    if (error.code === "auth/wrong-password") {
      showMessages("Contraseña incorrecta", "error");
    }
    if (error.code === "auth/invalid-email") {
      showMessages("Email invalido", "error");
    }
    if (error.code === "auth/missing-password") {
      showMessages("Ingresa tu contraseña", "error");
    }
    console.log(error);
  }
});
