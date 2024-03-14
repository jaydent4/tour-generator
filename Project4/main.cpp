//#include <cstdio>
//#include <iomanip>
//#include <iostream>
//#include <map>
//#include <vector>
//
//#include "geodb.h"
//#include "router.h"
//#include "stops.h"
//#include "tourcmd.h"
//#include "tour_generator.h"
//
//using namespace std;
//
//void print_tour(vector<TourCommand>& tcs)
//{
//    double total_dist = 0;
//    std::string direction;
//    double street_distance = 0;
//
//    cout << "Starting tour...\n";
//
//    for (size_t i = 0; i < tcs.size(); ++i)
//    {
//        if (tcs[i].get_command_type() == TourCommand::commentary)
//        {
//            cout << "Welcome to " << tcs[i].get_poi() << "!\n";
//            cout << tcs[i].get_commentary() << "\n";
//        }
//        else if (tcs[i].get_command_type() == TourCommand::turn)
//        {
//            cout << "Take a " << tcs[i].get_direction() << " turn on " << tcs[i].get_street() << endl;
//        }
//        else if (tcs[i].get_command_type() == TourCommand::proceed)
//        {
//            total_dist += tcs[i].get_distance();
//            if (direction.empty())
//                direction = tcs[i].get_direction();
//            street_distance += tcs[i].get_distance();
//            if (i+1 < tcs.size() && tcs[i+1].get_command_type() == TourCommand::proceed 
//                && tcs[i+1].get_street() == tcs[i].get_street() && tcs[i].get_street() != "a path")
//            {
//                continue;
//            }
//
//            cout << "Proceed " << std::fixed << std::setprecision(3) << street_distance << " miles " << direction << " on " << tcs[i].get_street() << endl;
//            street_distance = 0;
//            direction.clear();
//        }
//    }
//
//    cout << "Your tour has finished!\n";
//    cout << "Total tour distance: " << std::fixed << std::setprecision(3) << total_dist << " miles\n";
//}
//
//int main(int argc, char *argv[])
//{
//    if (argc != 3)
//    {
//        cout << "usage: BruinTour mapdata.txt stops.txt\n";
//        return 1;
//    }
//
//    GeoDatabase geodb;
//    if (!geodb.load(argv[1]))
//    {
//        cout << "Unable to load map data: " << argv[1] << endl;
//        return 1;
//    }
//
//    Router router(geodb);
//    TourGenerator tg(geodb, router);
//
//    Stops stops;
//    if (!stops.load(argv[2]))
//    {
//        cout << "Unable to load tour data: " << argv[2] << endl;
//        return 1;
//    }
//
//    std::cout << "Routing...\n\n";
//
//    vector<TourCommand> tcs = tg.generate_tour(stops);
//    if (tcs.empty())
//        cout << "Unable to generate tour!\n";
//    else
//        print_tour(tcs);
//}

#include "HashMap.h"
#include "geodb.h"
#include "router.h"

int main()
{
	GeoDatabase test;
	test.load("minimapdata.txt");
	//GeoPoint p1("1", "1");
	//GeoPoint p2("6", "1");
	//string streetn = test.get_street_name(p1, p2);
	//std::cout << streetn;

	//GeoPoint cp1("1", "1");
	//GeoPoint cp2("6", "2");
	//GeoPoint mid = midpoint(cp1, cp2);
	//std::vector<GeoPoint> gp = test.get_connected_points(cp1);
	//for (int i = 0; i < gp.size(); i++)
	//{
	//	std::cout << gp[i].sLatitude << " " << gp[i].sLongitude << endl;
	//}

	Router r(test);
	std::vector<GeoPoint> p = r.route(GeoPoint("1", "1"), GeoPoint("2", "8"));
	for (int i = 0; i < p.size(); i++)
	{
		std::cout << p[i].to_string() << endl;
	}
}
