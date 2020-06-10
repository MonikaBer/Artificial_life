#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Subjects/Animals/Herbivore.hpp"
#include "../Subjects/Animals/Predator.hpp"
#include "../Subjects/Plants/TypicalPlant.hpp"
#include "../Subjects/SubjectsCollection.hpp"
#include "../helper.hpp"

BOOST_AUTO_TEST_SUITE(test_suite_collection)

    BOOST_AUTO_TEST_CASE( testSingletonPattern )
    {
        SubjectsCollection &collection1 = SubjectsCollection::getInstance();
        SubjectsCollection &collection2 = SubjectsCollection::getInstance();
        BOOST_CHECK_EQUAL(&collection1, &collection2);
    }

    BOOST_AUTO_TEST_CASE( testStoredQuantity )
    {
        Subject *pom;
        SubjectsCollection &collection = SubjectsCollection::getInstance();
        SubjectsFactory &factory = SubjectsFactory::getInstance();
        //check for predators:
        int n = 11; 
        for(int i = 0; i<n; i++)
        {
            pom = factory.create(PREDATOR, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
            collection.push(dynamic_cast<Predator*>(pom));
        }
        BOOST_CHECK_EQUAL(collection.getPredatorsNumber(), n);
        BOOST_CHECK_EQUAL(collection.getPlantsNumber(), NULL);
        //check for plants:
        int m = 24; 
        for(int i = 0; i<m; i++)
        {
            pom = factory.create(TYPICAL_PLANT, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
            collection.push(dynamic_cast<Plant*>(pom));
        }
        BOOST_CHECK_EQUAL(collection.getPredatorsNumber(), n);
        BOOST_CHECK_EQUAL(collection.getPlantsNumber(), m);
    }

    BOOST_AUTO_TEST_CASE( testDeleteObjects )
    {
        //check deletion all:
        SubjectsCollection &collection = SubjectsCollection::getInstance();
        SubjectsFactory &factory = SubjectsFactory::getInstance();
        collection.deleteAllSubjects();
        BOOST_CHECK_EQUAL(collection.getPredatorsNumber(), NULL);
        //check deletion of Herbivore by coordinates
        int xHerb(60), yHerb(60), maxLifeTime(20), viewSize(20);
        Herbivore* tHerb = new Herbivore(xHerb, yHerb, maxLifeTime, viewSize);
        collection.push(tHerb);
        BOOST_CHECK_EQUAL(collection.getHerbivoresNumber(), 1);
        Coordinates predCoord = std::make_pair(xHerb, yHerb);
        collection.deleteHerbivore(predCoord);
        BOOST_CHECK_EQUAL(collection.getHerbivoresNumber(), 0);
        //check deletion of Predator by index:
        Subject *pom;
        int n = 7; 
        for(int i = 0; i<n; i++)
        {
            pom = factory.create(PREDATOR, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
            collection.push(dynamic_cast<Predator*>(pom));
        }
        BOOST_CHECK_EQUAL(collection.getPredatorsNumber(), n);
        collection.deletePredator(4);
        BOOST_CHECK_EQUAL(collection.getPredatorsNumber(), n-1);
    }

BOOST_AUTO_TEST_SUITE_END()