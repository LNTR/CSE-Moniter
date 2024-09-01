let port = null;

chrome.runtime.onStartup.addListener(() => {
  const webSocket = new WebSocket("ws://127.0.0.1:88");
  webSocket.onmessage = (event) => {
    sendMessageToPopup({ data: event.data });
  };
  chrome.action.setBadgeText({ text: "text" });
});

chrome.runtime.onConnect.addListener((p) => {
  port = p;
});

function sendMessageToPopup(message) {
  if (port) {
    port.postMessage({ message });
  }
}
