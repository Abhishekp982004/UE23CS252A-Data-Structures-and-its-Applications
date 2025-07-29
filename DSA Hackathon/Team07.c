#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store user information
typedef struct User {
    int id;
    char name[100];
    struct User *next;
} User;

// Structure to store product information
typedef struct Product {
    int id;
    char name[100];
    struct Product *next;
} Product;

// Structure to represent browsing history
typedef struct BrowsingHistory {
    int userId;
    int productId;
    struct BrowsingHistory *next;
} BrowsingHistory;

// Structure for the hash table
typedef struct HashTable {
    int size;
    User **userTable;
    Product **productTable;
} HashTable;

// Hash function to calculate index
int hashFunction(int key, int size) {
    return key % size;
}

// Function to initialize the hash table
HashTable *initializeHashTable(int size) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->userTable = (User **)malloc(size * sizeof(User *));
    table->productTable = (Product **)malloc(size * sizeof(Product *));
    for (int i = 0; i < size; i++) {
        table->userTable[i] = NULL;
        table->productTable[i] = NULL;
    }
    return table;
}

// Function to add a user to the hash table
void addUser(HashTable *table, int id, const char *name) {
    User *newUser = (User *)malloc(sizeof(User));
    newUser->id = id;
    strcpy(newUser->name, name);
    int index = hashFunction(id, table->size);
    newUser->next = table->userTable[index];
    table->userTable[index] = newUser;
}

// Function to add a product to the hash table
void addProduct(HashTable *table, int id, const char *name) {
    Product *newProduct = (Product *)malloc(sizeof(Product));
    newProduct->id = id;
    strcpy(newProduct->name, name);
    int index = hashFunction(id, table->size);
    newProduct->next = table->productTable[index];
    table->productTable[index] = newProduct;
}

// Function to track user browsing history
void addBrowsingHistory(BrowsingHistory **history, int userId, int productId) {
    BrowsingHistory *newEntry = (BrowsingHistory *)malloc(sizeof(BrowsingHistory));
    newEntry->userId = userId;
    newEntry->productId = productId;
    newEntry->next = *history;
    *history = newEntry;
}

// Function to generate recommendations for a user
void generateRecommendations(HashTable *table, BrowsingHistory *history, int userId) {
    BrowsingHistory *current = history;
    int found = 0;
    printf("Recommendations for User %d: ", userId);

    // Traverse browsing history to find products browsed by the user
    while (current != NULL) {
        if (current->userId == userId) {
            int index = hashFunction(current->productId, table->size);
            Product *product = table->productTable[index];
            while (product != NULL) {
                if (product->id == current->productId) {
                    printf("%s ", product->name);
                    found = 1;
                    break;
                }
                product = product->next;
            }
        }
        current = current->next;
    }

    if (!found) {
        printf("No recommendations found.");
    }
    printf("\n");
}

int main() {
    int tableSize = 10;
    int userId;
    HashTable *table = initializeHashTable(tableSize);
    BrowsingHistory *history = NULL;

    // Add users
    int numUsers;
    printf("Enter the number of users: ");
    scanf("%d", &numUsers);
    for (int i = 0; i < numUsers; i++) {
        int userId;
        char userName[100];
        printf("Enter user ID and name: ");
        scanf("%d %99s", &userId, userName);
        addUser(table, userId, userName);
    }

    // Add products
    int numProducts;
    printf("Enter the number of products: ");
    scanf("%d", &numProducts);
    for (int i = 0; i < numProducts; i++) {
        int productId;
        char productName[100];
        printf("Enter product ID and name: ");
        scanf("%d %99s", &productId, productName);
        addProduct(table, productId, productName);
    }

    // Track browsing history
    int numHistory;
    printf("Enter the number of browsing records: ");
    scanf("%d", &numHistory);
    for (int i = 0; i < numHistory; i++) {
        int userId, productId;
        printf("Enter user ID and product ID: ");
        scanf("%d %d", &userId, &productId);
        addBrowsingHistory(&history, userId, productId);
    }

    // Generate recommendations
    printf("Enter user ID to get recommendations: ");
    scanf("%d", &userId);
    generateRecommendations(table, history, userId);

    // Free allocated memory (simplified)
    // Ideally, we should free all allocated memory for users, products, and browsing history

    return 0;
}