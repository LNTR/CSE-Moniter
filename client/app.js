document.getElementById("subscribe-btn").addEventListener("click", function () {
  const stockSymbol = document.getElementById("stock").value;
  const priceThreshold = document.getElementById("price-threshold").value;

  if (stockSymbol && priceThreshold) {
    const notificationItem = document.createElement("li");
    notificationItem.textContent = `Subscribed to ${stockSymbol} - Notify when price drops below $${priceThreshold}`;
    document.getElementById("notifications").appendChild(notificationItem);

    document.getElementById("stock").value = "";
    document.getElementById("price-threshold").value = "";
  } else {
    alert("Please enter both a stock symbol and a price threshold.");
  }
});
