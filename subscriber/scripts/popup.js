let port = chrome.runtime.connect();

port.onMessage.addListener((response) => {
  console.log(response);
});
