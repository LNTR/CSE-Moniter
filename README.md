# Stock Notification System

This project is a C++ application that monitors stocks listed on the Colombo Stock Exchange and notifies subscribers of any price drops. Subscribers use a Chrome plugin to subscribe to specific stocks, and notifications are distributed through a middleware server.

## Project Structure

- `publisher`: Monitors stocks and publishes updates.
- `middleware`: Middleware server handling the distribution of notifications to subscribers.
- `subscriber`: A custom chrome plugin that allows users to subscribe to specific stocks.

## Features

- **Stock Monitoring**: `cli_publishers` continuously monitor stock prices on the Colombo Stock Exchange.
- **Subscriber Notifications**: Subscribers are notified in real-time when the price of a subscribed stock drops.
- **Chrome Plugin**: Users subscribe to specific stocks via a custom-developed Chrome plugin.

## Build Instructions

1. **Requirements**:
   - CMake 3.5 or higher
   - C++20 compatible compiler
   - Boost Libraries (json, url)
   - OpenSSL
   - [JWT-CPP](https://github.com/Thalhammer/jwt-cpp)
   - MySQL

2. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/stock-notification-system.git
   cd stock-notification-system```

## Build the Project
```
mkdir build
cd build
cmake ..
make
```

