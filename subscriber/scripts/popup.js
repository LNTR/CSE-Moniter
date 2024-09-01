document.querySelector(".control").addEventListener("click", () => {
  alert("Working");
});
chrome.runtime.onMessage.addListener(function (request, sender, sendResponse) {
  document.querySelector(".placeholder").innerHTML = request.message;
});
