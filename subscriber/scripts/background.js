chrome.runtime.onStartup.addListener(() => {
  chrome.runtime.sendMessage({ message: "hello from background" }, (res) => {
    console.log(res);
  });
  chrome.action.setBadgeText({ text: "text" });
});
