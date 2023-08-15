// importar función para crear usuario
import { createUserWithEmailAndPassword } from "https://www.gstatic.com/firebasejs/10.1.0/firebase-auth.js";
// importar firebase
import { auth } from "./firebase.js";
// importar función para mostrar mensajes
import { showMessages } from "./showMessages.js";
// registrar datos del formulario
const register = document.querySelector("#register");

// Registrar usuario
register.addEventListener("submit", async (e) => {
  // Evitar que se recargue la página
  e.preventDefault();

  // Obtener info del formulario
  const email = register["email"].value;
  const password = register["password"].value;

  try {
    // Crear usuario
    const userCredentials = await createUserWithEmailAndPassword(
      auth,
      email,
      password
    );
    // Mensaje de registro exitoso
    showMessages("Registrado correctamente", "success");
    // Redireccionar a login
    setTimeout(function () {
      window.location.href = "login.html";
    }, 2000);
  } catch (error) {
    // Mensaje de error email en uso
    if (error.code === "auth/email-already-in-use") {
      showMessages("El email ya está en uso", "error");
    }
    // Mensaje de error email no válido
    if (error.code === "auth/invalid-email") {
      showMessages("El email no es válido", "error");
    }
    // Mensaje de error contraseña débil
    if (error.code === "auth/weak-password") {
      showMessages("La contraseña debe tener al menos 6 caracteres", "error");
    }
  }
});