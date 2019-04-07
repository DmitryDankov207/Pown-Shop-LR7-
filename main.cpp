#include <stdlib.h>
#include <windows.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define ITEMBASEFILENAME "F://Development//items.txt"
#define CLIENTBASEFILENAME "F://Development//clients.txt"

using namespace std;

struct Item {
	int id;
	int clientId;
	char name[10];
	double cost;
	double pledge;
	char deliveryDate[8];
	int keepingTime;
};

struct Client {
	char name[10];
	char surname[20];
	char secondName[15];
	char passportNumber[10];
	char registrationDate[10];
	int id;
};

void openFile(FILE **file, const char* fileName) {
	(*file) = fopen(fileName, "r+");
	if (!(*file))
		exit(1);
}

void getClientListFromFile(vector <Client> *clients) {
	FILE *file;
	openFile(&file, CLIENTBASEFILENAME);
	while (!feof(file)) {
		Client client = Client();
		fscanf(file, "%s\n", client.name);
		fscanf(file, "%s\n", client.secondName);
		fscanf(file, "%s\n", client.surname);
		fscanf(file, "%s\n", client.passportNumber);
		fscanf(file, "%s\n", client.registrationDate);
		fscanf(file, "%d\n", &client.id);
		clients->push_back(client);
	}
}

void getItemListFromFile(vector <Item> *items) {
	FILE *file;
	openFile(&file, ITEMBASEFILENAME);
	while (!feof(file)) {
		Item item = Item();
		fscanf(file, "%s\n", item.name);
		fscanf(file, "%d\n", &item.id);
		fscanf(file, "%d\n", &item.clientId);
		fscanf(file, "%f\n", &item.cost);
		fscanf(file, "%s\n", item.deliveryDate);
		fscanf(file, "%d\n", &item.keepingTime);
		fscanf(file, "%f\n", &item.pledge);
		items->push_back(item);
	}
}

int getClient(vector<Client> *clients) {
	Client client = Client();
	cout << endl << "\tClient:" << endl;
	cout << "Name:" << endl;
	cin >> client.name;
	cout << "Second name:" << endl;
	cin >> client.secondName;
	cout << "Surname:" << endl;
	cin >> client.surname;
	cout << "Passport number:" << endl;
	cin >> client.passportNumber;
	cout << "Registration date:" << endl;
	cin >> client.registrationDate;
	client.id = clients->size();
	clients->push_back(client);
	return client.id;
}

int findClient(vector<Client> clients) {
	int id;
	while (true) {
		cout << endl << "Type ID(type -1 to quit): ";
		cin >> id;
		if (id == -1)
			return -1;
		for (auto client : clients)
			if (client.id == id)
				return client.id;
		cout << endl << "invalid ID!";
	}
}

void getItem(vector<Item> *items, int clientId) {
	Item item = Item();
	cout << endl << "\tItem:" << endl;
	cout << endl << "Item name:" << endl;
	cin >> item.name;
	cout << "Cost:" << endl;
	cin >> item.cost;
	cout << "Pledge:" << endl;
	cin >> item.pledge;
	cout << "Delivery date:" << endl;
	cin >> item.deliveryDate;
	cout << "Keeping time:" << endl;
	cin >> item.keepingTime;
	item.clientId = clientId;
	item.id = items->size();
	items->push_back(item);
}

void makeDelivery(vector<Item> *items, vector<Client> *clients) {
	int choice, id;
	while (true) {
		cout << endl << "(1)Create new" << endl;
		cout << "(2)Use existing client" << endl;
		cout << "(3)Return to menu" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			getItem(items, getClient(clients));
			break;
		case 2:
			id = findClient(*clients);
			if (id == -1)
				break;
			getItem(items, id);
			break;
		case 3:
			return;
		default:
			cout << endl << "invalid input!";
			break;
		}
	}
}

void showItem(Item item, bool idNeed = false) {
	cout << endl << "Name: " << item.name;
	cout << endl << "ID: " << item.id;
	cout << endl << "Cost: " << item.cost;
	cout << endl << "Pledge: " << item.pledge;
	cout << endl << "Delivery Date: " << item.deliveryDate;
	cout << endl << "Keeping time: " << item.keepingTime;
	if (idNeed)
		cout << endl << "Client ID:" << item.clientId;
}

void showClient(Client client, vector<Item> items) {
	cout << endl << "ID: " << client.id;
	cout << endl << "Name: " << client.name;
	cout << endl << "Surname: " << client.surname;
	cout << endl << "Second name: " << client.secondName;
	cout << endl << "Passport number: " << client.passportNumber;
	cout << endl << "Registration date: " << client.registrationDate;
	cout << endl << "Delivery history:" << endl;
	for (auto item : items)
		if (item.clientId == client.id) {
			showItem(item);
			cout << endl;
		}
}

void showBase(vector<Item> items, vector<Client> clients) {
	if(clients.size() > 0)
		for (auto client : clients) {
			showClient(client, items);
			cout << endl;
		}
	else
		for (auto item : items) {
			showItem(item);
			cout << endl;
		}
}

int countItemsCost(vector<Item> items) {
	int cost = 0;
	for (auto item : items)
		cost += item.cost;
	return cost;
}

int countItemsPledge(vector<Item> items) {
	int pledge = 0;
	for (auto item : items)
		pledge += item.pledge;
	return pledge;
}

void deleteClient(vector<Client> *clients) {
	int choice, clientId;
	while (true) {
		cout << endl << "(0)Exit" <<
			endl << "(1)Type client ID: ";
		cin >> choice;
		switch (choice) {
		case 0:
			break;
		case 1:
			cin >> clientId;
			if (clientId < 0 && clientId >= clients->size()) {
				cout << endl << "invalid input!";
				break;
			}
			for (auto client : *clients)
				if (client.id == clientId) {
					clients->erase(clients->begin() + client.id);
					return;
				}
		default:
			cout << endl << "invalid input!";
			break;
		}
	}
}

void deleteItem(vector<Item> *items) {
	int choice, itemId;
	while (true) {
		cout << endl << "(0)Exit" <<
			endl << "(1)Type item ID: ";
		cin >> choice;
		switch (choice) {
		case 0:
			break;
		case 1:
			cin >> itemId;
			if (itemId < 0 && itemId >= items->size()) {
				cout << endl << "invalid input!";
				break;
			}
			for (auto client : *items)
				if (client.id == itemId) {
					items->erase(items->begin() + client.id);
					return;
				}
		default:
			cout << endl << "invalid input!";
			break;
		}
	}
}

void saveItemList(vector<Item> items) {
	ofstream out;
	out.open(ITEMBASEFILENAME);
	for (auto item : items)
		out << item.name << endl <<
			item.id << endl <<
			item.clientId << endl <<
			item.cost << endl <<
			item.deliveryDate << endl <<
			item.keepingTime << endl <<
			item.pledge << endl;
	out.close();
}

void saveClientList(vector<Client> clients) {
	ofstream out;
	out.open(CLIENTBASEFILENAME);
	for (auto client : clients)
		out << client.name << endl <<
			client.secondName << endl <<
			client.surname << endl <<
			client.passportNumber << endl <<
			client.registrationDate << endl <<
			client.id << endl;
	out.close();
}

void runPownShopBaseMenu() {
	int choice;
	vector<Item> items;
	vector<Client> clients;
	getItemListFromFile(&items);
	getClientListFromFile(&clients);
	while (true) {
		cout << "\n(1)Add Delivery" << "\n(2)Delete Item" <<
			"\n(3)Delete Client" << "\n(4)Show base" <<
			"\n(5)Show potential salary" << "\n(6)Show cost of all items" <<
			"\n(0)Exit" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			makeDelivery(&items, &clients);
			break;
		case 2:
			deleteItem(&items);
			break;
		case 3:
			deleteClient(&clients);
			break;
		case 4:
			showBase(items, clients);
			break;
		case 5:
			cout << endl << "Potential salary from all items: " <<
				countItemsCost(items) - countItemsPledge(items) << endl;
			break;
		case 6:
			cout << endl << "Cost of all items: " <<
				countItemsCost(items) << endl;
			break;
		case 0:
			saveClientList(clients);
			cout << "\nv";
			saveItemList(items);
			return;
		default:
			cout << "\ninvalid input!";
			break;
		}
	}
}

int main() {
	runPownShopBaseMenu();
	return 0;
}