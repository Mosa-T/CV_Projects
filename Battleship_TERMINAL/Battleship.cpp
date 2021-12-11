#include "Battleship.h"

	Battleship::Battleship(int dim) {
		this->dim = dim;
		for (int i = 1; i <= dim; i++) {
			for (int j = 0; j < dim; j++) {
				friendly_ships_coord.push_back(std::pair<string, char>(std::string(1, (char)(j % dim + 'A')).append(std::to_string(i)), ' '));
				sea_targets.push_back(std::pair<string, char>(std::string(1, (char)(j % dim + 'A')).append(std::to_string(i)), ' '));
			}
		}
	}

	void Battleship::restart() {
		(friendly_ships_coord).clear();
		for (int i = 0; i < dim * dim; i++) {
			for (int j = 0; j < dim; j++) {
				friendly_ships_coord.push_back(std::pair<string, char>(std::string(1, (char)(j % dim + 'A')).append(std::to_string(i)), ' '));
				sea_targets.push_back(std::pair<string, char>(std::string(1, (char)(j % dim + 'A')).append(std::to_string(i)), ' '));
			}
		}
	}

	void Battleship::draw_grid() {
		string temp;
		temp = "           ";
		string temp2 = "        ";
		for (int j = 0; j < dim; j++) {
			temp.append(std::string(std::string(1, friendly_ships_coord.at(j).first.at(0)) + "   "));
			temp2.append(std::string(std::string(1, sea_targets.at(j).first.at(0)) + "   "));
		}
		cout << temp << temp2<< endl;
		
		
		for (int i = 0; i < dim; i++) {
			if (i >= 9) {
				temp = "";
				temp2 = "";
				temp.append(string("       " + std::string(std::string(1, friendly_ships_coord.at(i * dim).first.at(1))+ std::string(1, friendly_ships_coord.at(i * dim).first.at(2)) + "  ")));
				temp2.append(string("       " + std::string(std::string(1, sea_targets.at(i * dim).first.at(1)) + std::string(1, sea_targets.at(i * dim).first.at(2)) + "  ")));
				for (int j = 0; j < dim; j++) {
					if (j + 1 == dim) {
						temp.append(std::string(std::string(1, friendly_ships_coord.at(j + i * dim).second)  + ""));
						temp2.append(std::string(std::string(1, sea_targets.at(j + i * dim).second) + ""));
						continue;
					}
					temp.append(std::string(std::string(1, friendly_ships_coord.at(j + i * dim).second) + " | "));
					temp2.append(std::string(std::string(1, sea_targets.at(j + i * dim).second) + " | "));
				}
				cout << temp << temp2<< endl;
			}
			else {
				temp = "";
				temp.append(string("	" + std::string(std::string(1, friendly_ships_coord.at(i * dim).first.at(1)) + "  ")));
				temp2 = "";
				temp2.append(string("	" + std::string(std::string(1, sea_targets.at(i * dim).first.at(1)) + "  ")));
				for (int j = 0; j < dim; j++) {
					if (j + 1 == dim) {
						temp.append(std::string(std::string(1, friendly_ships_coord.at(j + i * dim).second) + "  "));
						temp2.append(std::string(std::string(1, sea_targets.at(j + i * dim).second) + "  "));
						continue;
					}
					temp.append(std::string(std::string(1, friendly_ships_coord.at(j + i * dim).second) + " | "));
					temp2.append(std::string(std::string(1, sea_targets.at(j + i * dim).second) + " | "));
				}
				cout << temp << temp2 << endl;
			}
			if (i + 1 != dim) {
				temp = "	  ";
				for (int j = 1; j < dim+1; j++) {
					if (((j)%dim)) {
						temp.append("---|");
						continue;
					}
					temp.append("---");
				}
				cout << temp<< temp << endl;
			}
			else {
				cout << endl << "							Friendly ships	" << "												enemy ships									";
				cout << endl;
			}
		}
	}
	
		bool Battleship::check_coords(string s, vector<string> vc_temp, int i, vector<string> vc) {
		cout << "\nWE CHECKING COORDS\n";
		if (s.size() < 2 || s.size() > 3) {
			cout << "\nIncorrect syntax for coordinate, please try again" << endl;
			return false;
		}
		string s0 = s.substr(1);
		if (s0.size() == 1) {
			if (!isdigit(s0.at(0))) {
				cout << "\nIncorrect syntax for coordinate, please try again_2" << endl;
				return false;
			}
		}
		else {
			if (!isdigit(s0.at(0)) && !isdigit(s0.at(1))) {
				cout << "\nIncorrect syntax for coordinate, please try again_3" << endl;
				return false;
			}
		}
		int s1 = stoi(s0);
		if (s1 > dim || s1  <= 0 || s.at(0) - 'A' >= dim || s.at(0) - 'A' < 0) {
			cout << "\nOut of bounds coordinate, please try again" << endl;
			return false;
		}
		if ((find(vc_temp.begin(), vc_temp.end(), s)) != vc_temp.end()) {
			cout << "\nCoordinate already has an been assigned, please try again" << endl;
			return false;
		}
		/* check that coordinates are linear on each ship.
		if(i != 0){
			for(auto k : vc){
				if(k
			}
		}
		*/
		return true;
	}

	void Battleship::set_ships() {

		string s;

		vector<string> vc;

		vector<string> vc_temp;

		//std::transform(s.begin(), s.end(), s.begin(), ::toupper);

		cout << "You have " << 5 << " ships to place:" << endl;

		cout << "Set Carrier coordinates one by one(5)" << endl;

		for (int i = 0; i < ship_sets.get_points_carrier(); i++) {

			cout << "Coordinate #" << (i + 1) << ": ";

			cin >> s;

			s.at(0) = ::toupper(s.at(0));

			if (!(check_coords(s, vc_temp, i, vc))) {

				i--;

				continue;

			}

			vc_temp.push_back(s);

			vc.push_back(s);

			//if(i+1 == ship_sets.get_points_carrier()){ this is supposed to be checking if the coordinates are lined? dunno

				//if(vc.at(0)

			//}

		}

		ship_sets.set_coord_carrier(vc);

		vc.clear();

		s = "";

		cout << "Set Battleship coordinates one by one(4)" << endl;

		for (int i = 0; i < ship_sets.get_points_battleship(); i++) {

			cout << "Coordinate #" << (i + 1) << ": ";

			cin >> s;

			s.at(0) = ::toupper(s.at(0));

			if (!(check_coords(s, vc_temp, i, vc))) {

				i--;

				continue;

			}

			vc_temp.push_back(s);

			vc.push_back(s);

		}

		ship_sets.set_coord_battleship(vc);

		vc.clear();

		s = "";

		cout << "Set Destroyer coordinates one by one(3)" << endl;

		for (int i = 0; i < ship_sets.get_points_destroyer(); i++) {

			cout << "Coordinate #" << (i + 1) << ": ";

			cin >> s;

			s.at(0) = ::toupper(s.at(0));

			if (!(check_coords(s, vc_temp, i, vc))) {

				i--;

				continue;

			}

			vc_temp.push_back(s);

			vc.push_back(s);

		}

		ship_sets.set_coord_destroyer(vc);

		vc.clear();

		s = "";

		cout << "Set Submarine coordinates one by one(3)" << endl;

		for (int i = 0; i < ship_sets.get_points_submarine(); i++) {

			cout << "Coordinate #" << (i + 1) << ": ";

			cin >> s;

			s.at(0) = ::toupper(s.at(0));

			if (!(check_coords(s, vc_temp, i, vc))) {

				i--;

				continue;

			}

			vc_temp.push_back(s);

			vc.push_back(s);

		}

		ship_sets.set_coord_submarine(vc);

		vc.clear();

		s = "";

		cout << "Set Patrol Boat coordinates one by one(2)" << endl;

		for (int i = 0; i < ship_sets.get_points_patrol_boat(); i++) {

			cout << "Coordinate #" << (i + 1) << ": ";

			cin >> s;

			s.at(0) = ::toupper(s.at(0));

			if (!(check_coords(s, vc_temp, i, vc))) {

				i--;

				continue;

			}

			vc_temp.push_back(s);

			vc.push_back(s);

		}

		ship_sets.set_coord_patrol_boat(vc);

		vc.clear();

		vc_temp.clear();

		s = "";



		vector<string> coords;

		for (std::pair<std::string, char>& var : friendly_ships_coord)

		{

			coords.clear();

			coords = ship_sets.get_carrier_coord();

			if ((find(coords.begin(), coords.end(), var.first)) != coords.end()) {

				var.second = 'C';

				continue;

			}

			coords.clear();

			coords = ship_sets.get_battleship_coord();

			if ((find(coords.begin(), coords.end(), var.first)) != coords.end()) {

				var.second = 'B';

				continue;

			}

			coords.clear();

			coords = ship_sets.get_destroyer_coord();

			if ((find(coords.begin(), coords.end(), var.first)) != coords.end()) {

				var.second = 'D';

				continue;

			}

			coords.clear();

			coords = ship_sets.get_submarine_coord();

			if ((find(coords.begin(), coords.end(), var.first)) != coords.end()) {

				var.second = 'S';

				continue;

			}

			coords.clear();

			coords = ship_sets.get_patrol_boat_coord();

			if ((find(coords.begin(), coords.end(), var.first)) != coords.end()) {

				var.second = 'P';

				continue;

			}

		}

		return;

	}

	int Battleship::attacked_square(string grid_coord) {
		grid_coord.at(0) = ::toupper(grid_coord.at(0));
		//std::transform(grid_coord.begin(), grid_coord.end(), grid_coord.begin(), ::toupper);
		auto it = std::find_if(friendly_ships_coord.begin(), friendly_ships_coord.end(),[&grid_coord](const std::pair<std::string, char>& element) { return element.first == grid_coord; });
		
		if (it->second != ' ' && it->second != 'X') {
			switch(it->second){
				case 'C':
					ship_sets.carrier_hit(it->first);
					break;
				case 'B':
					ship_sets.battleship_hit(it->first);
					break;
				case 'D':
					ship_sets.destroyer_hit(it->first);
					break;
				case 'S':
					ship_sets.submarine_hit(it->first);
					break;
				case 'P':
					ship_sets.patrol_boat_hit(it->first);
					break;
			}
			it->second = 'X';
			return 1;
		}
		return 0;
	}
	
	void Battleship::mark_hit(string grid_coord) {
		grid_coord.at(0) = ::toupper(grid_coord.at(0));
		
		auto it = std::find_if(sea_targets.begin(), sea_targets.end(),[&grid_coord](const std::pair<std::string, char>& element) { return element.first == grid_coord; });
		
		if (it != sea_targets.end()) {
			cout <<"it != sea_targets.end()"<<endl;
			it->second = 'X';
			return;
		}
			cout <<"SHIT OUT OF LUCK BUDDY IT DIDNT WORK"<<endl;
	}

	bool Battleship::did_i_lose() {
		if (!ship_sets.get_points_battleship() && !ship_sets.get_points_carrier() && !ship_sets.get_points_destroyer() && !ship_sets.get_points_patrol_boat() && !ship_sets.get_points_submarine())
			return true;
		return false;
	}



	void Battleship::start(){
		struct sockaddr_in srv_addr;
		int   sock_fd;
		srv_addr.sin_family = AF_INET;
		srv_addr.sin_port = P_SRV_PORT-3;
		srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			error("Client - Socket creation error \n");
		printf("\nClient - Socket created\n");
		if (connect(sock_fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0)
			error("\nClient - Connection Failed \n");
		printf("\nClient - Connection succeeded\n");
		while(!did_i_lose()){
			turn_handle(sock_fd);
		}
		cout << "\nClient - Game over - you lost all your ships!\n";
	}

	void Battleship::turn_handle(int sock)
	{
		Battleship board(10);
		msg_dirhdr_t turn;
		msg_ack_turn_t turn_ack;
		msg_notify_t attacked_notify;
		msg_dirhdr_t hit_or_miss;
		msg_ack_t ack_back;
		ack_back.m_type = MSG_ACK;
		turn_ack.m_type = MSG_TURN;
		board.draw_grid();
		board.set_ships();
		board.draw_grid();
		if(write(sock,&ack_back,sizeof(ack_back))<0){ 
					error("\nClient - Error sending turn_ack\n");
		}
		if(recv(sock,&ack_back,sizeof(turn),0)<0){
			error("\nClient - Error: couldn't receive turn msg\n");
		}
		printf("\nClient - Socket number [%d]\n",sock);
		printf("\nClient - Waiting for turn setup\n");
		if(recv(sock,&turn,sizeof(turn),0)<0){
			error("\nClient - Error: couldn't receive turn msg\n");
		}
		printf("\nClient - received turn setup\n");
		while(1){
			printf("\nClient - turn signal = %d\n",turn.m_count);
			printf("\nClient - received turn msg \n");
			if(turn.m_type != MSG_DIRHDR){
				printf("\nClient - turn.m_type = %d \n",turn.m_type);
				error("\nClient - turn msg type wrong\n");
			}
			if(turn.m_count == 1){
				printf("\nClient - Wait for your turn\n");
				if(recv(sock,&attacked_notify,sizeof(attacked_notify),0)<0){
					error("\nClient - attacked_notify error\n");
				}
				printf("\nClient - received attack coordinates\n");
				string coords = string(attacked_notify.m_name);
				cout << "Client - coordinate to check: "<<coords<<endl;
				hit_or_miss.m_count = board.attacked_square(coords);
				cout <<"Client - Was it a hit?: "<<hit_or_miss.m_count<<endl;
				if(write(sock,&hit_or_miss,sizeof(hit_or_miss))<0){
					error("\nClient - hit_or_miss error\n");
				}
				printf("\nClient - sent hit_or_miss\n");
				if(recv(sock,&turn,sizeof(turn),0)<0){
					error("\nClient - recv from Client error\n"); 				
				}
				printf("\nClient - received turn update\n");
				turn_ack.m_type = MSG_TURN;
				printf("\nClient - send ack for received turn update to server\n");
				if(write(sock,&ack_back,sizeof(ack_back))<0){ 
					error("\nClient - Error sending turn_ack\n");
				}
				printf("\nClient - sent ack for received turn update to server\n");
				if(board.did_i_lose()){
				//send server you lost.
				cout << "\nClient - YOU LOSE\n";
				}
				board.draw_grid();
			}
			if(turn.m_count == 1){
				error("\nClient - Error switching turn.m_count value\n");
			}
			printf("\nClient - Your turn now!\n");
			char name[P_NAME_LEN];
			printf("\nClient - Enter a coordinate to hit: ");
			scanf("%s", name);
			printf("\nClient - Your coordiante is %s.\n", name);
			cout << "\nClient - Your coordiante in C++ is:" << string(name)<<endl;
			msg_notify_t temp;
			msg_ack_t temp_ack;
			temp.m_type = MSG_NOTIFY;
			strcpy(temp.m_name,name);
			temp.m_addr = inet_addr( "127.0.0.1" );
			temp.m_port = 0;
			printf("\nClient - sending MSG_NOTIFY\n");
			if( write(sock,&temp,sizeof(temp)) < 0 ){
				error("\nClient - sending notify\n");
			}
			printf("\nClient - sent MSG_NOTIFY\n");
			if( recv(sock,&temp_ack,sizeof(temp_ack),0) <0 )
				error("\nClient - recv from Client error\n");
			printf("\nClient - share: receiving MSG_ACK\n");
			if( temp_ack.m_type != MSG_ACK){
				error("\nClient - type recived not msg ack\n");
			}
			msg_dirhdr_t attack_bool;	
			printf("\nClient - waiting to receive if hit or miss\n");
			if( recv(sock,&attack_bool,sizeof(attack_bool),0) <0 ){
				error("\nClient - recv from Client error\n");
			}
			if(attack_bool.m_count == 0){
				printf("\nClient -  MISSED! \n");
			} else if(attack_bool.m_count == 1){
				printf("\nClient -  HIT!! \n");
				string hit_mark = string(name);
				mark_hit(hit_mark);
				cout << "Client - Hit coordinate mark: " << hit_mark<<endl;
			} 
			turn_ack.m_type = MSG_TURN;
			printf("\nClient - Send MSG_TURN to server\n");
			if(write(sock,&turn_ack,sizeof(turn_ack))<0){
				error("\nClient- Error sending turn_ack\n");
			}
			if(recv(sock,&turn,sizeof(turn),0)<0){
				error("\nClient - Error: couldn't receive turn msg\n");
			}
			printf("\nClient - received MSG_DIRHDR - turn swap\n");
	
			printf("\nClient - send MSG_ACK for MSG_DIRHDR\n");
			if(write(sock,&ack_back,sizeof(ack_back))<0){
				error("\nClient- Error sending turn_ack\n");
			}
			printf("\nClient - sent MSG_ACK for MSG_DIRHDR\n");
			//add recv to receive if win condition was met
			//add "YOU WON" if so.
			board.draw_grid();
		}
		return;
	}

	void Battleship::error(const char * str)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
int main() {
	Battleship a;
	a.start();
	return 0;
}
