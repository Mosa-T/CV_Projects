#include "View.h"

View* View::ptr3 = 0;

View& View::get_Instance() {
	if (!ptr3)
		ptr3 = new View();
	return *ptr3;
}


View::View()
{
	display_size = 25;
	origin = Coordinate(0, 0);
	origin.SetX(0);
	origin.SetY(0);
	updated = false;
	scale = 2.00;
}


void View::show()
{
	cout << "Display size: " << display_size << " scale: " << scale << " origin: (" << origin.GetX() << ", " << origin.GetY() << ")" << endl;
	int topNumY = origin.GetY() + (scale * display_size) - scale;
	int topNumX = origin.GetX() + (scale * display_size) - scale;
	int numY = topNumY;
	int numX = topNumX;
	int true_yy = ((origin.GetY() * -1) + (display_size * scale));
	for (int i = display_size; i > 0; i--)
	{
		int true_y = ((origin.GetY() * -1) + (i * scale));
		if ((int)((numY+origin.GetY()*-1)) % 3 == 0) // insert new num at first row in the collumn
		{
			cout << setw(3) << numY;
		}
		else {
			cout << setw(3) << "|";
		}

		numX = origin.GetX();
		for (int row_i = display_size; row_i > 0; row_i--)//while getting new line fill that line
		{
			int true_x = 0;
			if (print_obj((numX), (numY))); // insert scale to find
			else {
				cout << " .";
			}
			numX = numX + scale;
		}
		numY = numY - scale;
		cout << endl;
	}
	int num_x = origin.GetX();
	cout << "  ";
	for (int i = 0; i < display_size; i++) ////////// last line aka X line
	{
		if (i % 3 == 0)
			cout << setw(2) << num_x;
		else
			cout << "  ";
		num_x = num_x + scale;
	}
	cout << endl;
	updated = false;
}

void View::size(string str_i)
{
	if (!has_only_digits(str_i))
		throw string("ERROR: size must have only positive numbers");
	int i = stoi(str_i);
	if (i > 30) throw string("ERROR: new map size is too big.");
	if (i < 6) throw string("ERROR: new map size is too small.");
	this->display_size = i;
}

void View::zoom(string str_zoom)
{

	if (!has_only_digits(str_zoom))
		throw string("ERROR: size must have only positive numbers");
	int a = stod(str_zoom);
	if (a <= 0) throw string("ERROR: New map scale must be positive.");
	this->scale = a;
}

void View::pan(vector<string> xy)
{
	float a = stof(xy[0]);
	float b = stof(xy[1]);
	if (xy[0].at(0) == '-') {
		xy[0].erase(xy[0].begin());
	}
	if (xy[1].at(0) == '-') {
		xy[1].erase(xy[1].begin());
	}
	if (!all_of(begin(xy[0]), end(xy[0]), [](char c) { return isdigit(c); }) || !all_of(begin(xy[1]), end(xy[1]), [](char c) { return isdigit(c); }))
		throw string("ERROR : coordinate pan must have only numbers");
	try {
		this->origin.SetX(a);
		this->origin.SetY(b);
	}
	catch (string e) {
		cout << e;
	}
}

void View::updates(float x, float y, string id) {
	pair<int, int> b = { x,y };
	idAsKey[id] = b;
	Coordinate_As_key[b] = id;
}

bool View::print_obj(int x, int y)
{
	if (Coordinate_As_key.find({ x,y }) != Coordinate_As_key.end()) {
		std::map<pair<int, int>, std::string>::iterator it;
		it = Coordinate_As_key.find({ x,y });
		cout << it->second;
		Coordinate_As_key.erase({ x,y });
		return true;
	}
	for (int p = 1; p < scale; p++) {

		if (Coordinate_As_key.find({ x + p,y }) != Coordinate_As_key.end()) {
			std::map<pair<int, int>, std::string>::iterator it;
			it = Coordinate_As_key.find({ x + p,y });
			cout << it->second;
			Coordinate_As_key.erase({ x + p,y });
			return true;
		}
		else if (Coordinate_As_key.find({ x,y + p }) != Coordinate_As_key.end()) {
			std::map<pair<int, int>, std::string>::iterator it;
			it = Coordinate_As_key.find({ x,y + p });
			cout << it->second;
			Coordinate_As_key.erase({ x,y + p });
			return true;

		}
		else if (Coordinate_As_key.find({ x + p,y + p }) != Coordinate_As_key.end()) {
			std::map<pair<int, int>, std::string>::iterator it;
			it = Coordinate_As_key.find({ x + p,y + p });
			cout << it->second;
			Coordinate_As_key.erase({ x + p,y + p });
			return true;

		}
		else if (Coordinate_As_key.find({ x - p,y }) != Coordinate_As_key.end()) {
			std::map<pair<int, int>, std::string>::iterator it;
			it = Coordinate_As_key.find({ x - p,y });
			cout << it->second;
			Coordinate_As_key.erase({ x - p,y });
			return true;

		}
		else if (Coordinate_As_key.find({ x,y - p }) != Coordinate_As_key.end()) {
			std::map<pair<int, int>, std::string>::iterator it;
			it = Coordinate_As_key.find({ x,y - p });
			cout << it->second;
			Coordinate_As_key.erase({ x,y - p });
			return true;

		}
		else if (Coordinate_As_key.find({ x - p,y - p }) != Coordinate_As_key.end()) {
			std::map<pair<int, int>, std::string>::iterator it;
			it = Coordinate_As_key.find({ x - p,y - p });
			cout << it->second;
			Coordinate_As_key.erase({ x - p,y - p });
			return true;

		}
		else if (Coordinate_As_key.find({ x + p,y - p }) != Coordinate_As_key.end()) {
			std::map<pair<int, int>, std::string>::iterator it;
			it = Coordinate_As_key.find({ x + p,y - p });
			cout << it->second;
			Coordinate_As_key.erase({ x + p,y - p });
			return true;

		}
		else if (Coordinate_As_key.find({ x - p,y + p }) != Coordinate_As_key.end()) {
			std::map<pair<int, int>, std::string>::iterator it;
			it = Coordinate_As_key.find({ x - p,y + p });
			cout << it->second;
			Coordinate_As_key.erase({ x - p,y + p });
			return true;

		}

	}
	return false;
}
