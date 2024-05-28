#include "smarthomeconnect.h" 

int main() 
{ 
	smart_home_client::SmartHomeConnect client;
	client.StartConnection();

	return 0; 
}
