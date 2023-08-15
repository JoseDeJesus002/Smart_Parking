const loggedOut = document.querySelectorAll(".logged-out");
const loggedIn = document.querySelectorAll(".logged-in");

export const loginCheck = (user) => {
  if (user) {
    loggedIn.forEach((link) => (link.style.display = "block"));
    loggedOut.forEach((link) => (link.style.display = "none"));
  } else {
    loggedIn.forEach((link) => (link.style.display = "none"));
    loggedOut.forEach((link) => (link.style.display = "block"));
  }
};
