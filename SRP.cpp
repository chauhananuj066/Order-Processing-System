#include <iostream>
#include <string>

using namespace std;

class Order {
private:
    string productName;
    int quantity;
    double price; // Renamed from getPrice to price

public:
    // Constructor
    Order(string name, int qty, double price) 
        : productName(name), quantity(qty), price(price) {}

    // Getters
    string getProductName() { return productName; }

    int getQuantity() { return quantity; }
    
    double getPrice() { return price; }

    // Calculate Total Price
    double getTotalAmount() {
        return quantity * price; // Corrected member variable usage
    }

    // Display Order Details
    void displayOrder() {
        cout << "Order Details:\n";
        cout << "Product: " << productName << "\n";
        cout << "Quantity: " << quantity << "\n";
        cout << "Unit Price: $" << price << "\n";
        cout << "Total Amount: $" << getTotalAmount() << "\n";
    }
};

// Abstract class for Payment
class PaymentMethod {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentMethod() {}
};

// Concrete classes implementing different payment methods
class CreditCardPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing Credit Card Payment of $" << amount << endl;
    }
};

class PayPalPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal Payment of $" << amount << endl;
    }
};

class UPIPayment : public PaymentMethod {
public:
    void processPayment(double amount) override {
        cout << "Processing UPI Payment of $" << amount << endl;
    }
};

// Interface for Notification
class NotificationService {
public:
    virtual void sendNotification(string message) = 0;
    virtual ~NotificationService() {}
};

// Concrete Notification Classes
class EmailNotification : public NotificationService {
public:
    void sendNotification(string message) override {
        cout << "Sending Email: " << message << endl;
    }
};

class SMSNotification : public NotificationService {
public:
    void sendNotification(string message) override {
        cout << "Sending SMS: " << message << endl;
    }
};

// Create OrderProcessor to Handle Order Processing
class OrderProcessor {
private:
    PaymentMethod* paymentMethod;
    NotificationService* notificationService;

public:
    OrderProcessor(PaymentMethod* payMethod, NotificationService* notifyService)
        : paymentMethod(payMethod), notificationService(notifyService) {}

    void processOrder(Order order) {
        cout << " Your Order is processing : " << order.getProductName() << endl;
        paymentMethod->processPayment(order.getTotalAmount()); // Fixed to get total amount
        notificationService->sendNotification("Your order for " + order.getProductName() + " is confirmed.");
    }
};

int main() {
    // Creating an Order
    Order order("Laptop", 2, 1200.50);
    order.displayOrder(); // Display order details
    order.getTotalAmount(); // Calculate total amount
    order.getPrice(); // Get unit price
    order.getQuantity(); // Get quantity


    // Choosing Payment Method
    PaymentMethod* payment = new CreditCardPayment();
    // PaymentMethod* payment = new PayPalPayment();  // Uncomment to change payment method

    // Choosing Notification Type
    NotificationService* notification = new EmailNotification();
    // NotificationService* notification = new SMSNotification();  // Uncomment to change notification type

    // Processing the Order
    OrderProcessor processor(payment, notification);
    processor.processOrder(order);

    // Cleaning up memory
    delete payment;
    delete notification;

    return 0;
}
