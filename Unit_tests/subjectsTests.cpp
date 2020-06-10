#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Subjects/Animals/Herbivore.hpp"
#include "../Subjects/Animals/Predator.hpp"
#include "../Subjects/Plants/TypicalPlant.hpp"
#include "../Subjects/SubjectsCollection.hpp"
#include "../helper.hpp"
#include "../SimulationParameters.hpp"

    const double PERCENT_OF_REGENERATION = 0.1;
    const double ESSENTIAL_PERCENT_OF_ENERGY = 0.2;
    const double ESSENTIAL_PERCENT_OF_FULLNESS = 0.2;
    const double TEMPERATE_PERCENT_OF_FULLNESS = 0.5;
    const double TEMPERATE_PERCENT_OF_ENERGY = 0.3;
    const double SUFFICIENT_PERCENT_OF_FULLNESS = 0.85;

BOOST_AUTO_TEST_SUITE(test_suite_subjects);

    BOOST_AUTO_TEST_CASE( testSubjectConstructor )
    {
        int x(123), y(887), maxLifeTime(250), viewSize(100);
        Subject *tSub1 = new Subject(x, y);
        BOOST_CHECK_EQUAL(tSub1->getXPosition(), x);
        BOOST_CHECK_EQUAL(tSub1->getYPosition(), y);
        delete tSub1;
        tSub1 = nullptr;

        x = 443, y = -5;
        Subject *tSub2 = new TypicalPlant(x, y);
        BOOST_CHECK_EQUAL(tSub2->getXPosition(), x);
        BOOST_CHECK_EQUAL(tSub2->getYPosition(), y);
        delete tSub2;
        tSub2 = nullptr;

        x = 1, y = -1;
        Subject *tSub3 = new Herbivore(x, y, maxLifeTime, viewSize);
        BOOST_CHECK_EQUAL(tSub3->getXPosition(), x);
        BOOST_CHECK_EQUAL(tSub3->getYPosition(), y);
        delete tSub3;
        tSub3 = nullptr;

        x = 33, y = 1456;
        Subject *tSub4 = new Predator(x, y, maxLifeTime, viewSize);
        BOOST_CHECK_EQUAL(tSub4->getXPosition(), x);
        BOOST_CHECK_EQUAL(tSub4->getYPosition(), y);
        delete tSub4;
        tSub4 = nullptr;
    }

    BOOST_AUTO_TEST_CASE( testDetermineTarget)
    {
        //preparle Subject to tests:
        int x(50), y(50), maxLifeTime(10), viewSize(20);
        bool isReproductionPeriod = false;
        Herbivore *tSub = new Herbivore(x, y, maxLifeTime, viewSize);
        tSub->setMaxEnergy(100);
        tSub->setMaxFullness(100);
        tSub->setFullness(100);
        //check if Target is correctly set on DEAD status
        tSub->setEnergy(0);
        Target tar = tSub->determineTarget(isReproductionPeriod);
        BOOST_CHECK_EQUAL(tar, DEAD);
        //check if Target is correctly set on PARTNER status
        isReproductionPeriod = true;
        tSub->setEnergy(50);
        tar = tSub->determineTarget(isReproductionPeriod);
        BOOST_CHECK_EQUAL(tar, PARTNER);
        //check if Target is correctly set on SLEEP status
        isReproductionPeriod = false;
        tSub->setEnergy(10);
        tar = tSub->determineTarget(isReproductionPeriod);
        BOOST_CHECK_EQUAL(tar, SLEEP);
        //check is Target is correctly set on FOOD status
        tSub->setEnergy(100);
        tSub->setFullness(10);
        tar = tSub->determineTarget(isReproductionPeriod);
        BOOST_CHECK_EQUAL(tar, FOOD);

    }

    BOOST_AUTO_TEST_CASE( testIsVisibleForAnimals )
    {
        SubjectsCollection &collection = SubjectsCollection::getInstance();
        int xHerb(50), yHerb(50), xPred(40), yPred(45), maxLifeTime(10), viewSize(20);
        bool isReproductionPeriod = false;
        Herbivore *tHerb = new Herbivore(xHerb, yHerb, maxLifeTime, viewSize);
        //creating Predator close enough to Herbivore to see it. 
        Predator *tPred = new Predator(xPred, yPred, maxLifeTime, viewSize);
        collection.push(tHerb);
        collection.push(tPred);
        bool isVisible = tHerb->isVisibleForAnimal(std::make_pair(xPred, yPred));
        BOOST_CHECK_EQUAL(isVisible, true);
        //creating predator far away from herbivore:
        collection.deletePredator(0);
        xPred = 10;
        yPred = 10;
        tPred = new Predator(xPred, yPred, maxLifeTime, viewSize);
        collection.push(tPred);
        isVisible = tHerb->isVisibleForAnimal(std::make_pair(xPred, yPred));
        BOOST_CHECK_EQUAL(isVisible, false);
        collection.deleteAllSubjects();
    } 

    BOOST_AUTO_TEST_CASE( testAnimalLookAround )
    {
        //tests for Herbivore:
        AreaMap &map = AreaMap::getInstance(); 
        SubjectsCollection &collection = SubjectsCollection::getInstance();

        int xHerb(50), yHerb(50), xPlant(40), yPlant(40), maxLifeTime(10), viewSize(20);
        bool isReproductionPeriod = false;
        //add herbivore to collection and map
        Herbivore *tHerb1 = new Herbivore(xHerb, yHerb, maxLifeTime, viewSize);
        collection.push(tHerb1);
        map.insert(std::make_pair(xHerb, yHerb), tHerb1);
        //add plant to collection and map
        TypicalPlant *tPlant = new TypicalPlant(xPlant, yPlant);
        collection.push(tPlant);
        map.insert(std::make_pair(xPlant, yPlant), tPlant);
        //check if herbivore will find position of plant:
        Coordinates targetPos = std::make_pair(1, 1);
        Target tar = FOOD;
        bool result = tHerb1->lookAround(map, targetPos, tar, isReproductionPeriod);
        BOOST_CHECK_EQUAL(targetPos.first, xPlant);
        BOOST_CHECK_EQUAL(targetPos.second, yPlant);

        //now creating second Herbivore and set reproductionPeriod:
        int xHerb2 = xHerb+10;
        int yHerb2 = yHerb+10;
        isReproductionPeriod = true;
        Herbivore *tHerb2 = new Herbivore(xHerb2, yHerb2, maxLifeTime, viewSize);
        collection.push(tHerb2);
        map.insert(std::make_pair(xHerb2, yHerb2), tHerb2);
        //check if herbivore will find partner to reproduce
        tar = PARTNER;
        result = tHerb2->lookAround(map, targetPos, tar, isReproductionPeriod);
        BOOST_CHECK_EQUAL(targetPos.first, xHerb2);
        BOOST_CHECK_EQUAL(targetPos.second, yHerb2);

        //tests for Herbivore meeting Predator
        isReproductionPeriod = false;
        int xPred(52), yPred(52);
        Predator *tpred = new Predator(xPred, yPred, maxLifeTime, viewSize);
        collection.push(tpred);
        map.insert(std::make_pair(xPred, yPred), tpred);
        result = tHerb1->lookAround(map, targetPos, tar, isReproductionPeriod);
        BOOST_CHECK_EQUAL(tar, ESCAPE);
        BOOST_CHECK_EQUAL(targetPos.first, xPred);
        BOOST_CHECK_EQUAL(targetPos.second, yPred);

        //test for predator looking for food
        tar = FOOD;
        result = tpred->lookAround(map, targetPos, tar, isReproductionPeriod);
        BOOST_CHECK_EQUAL(targetPos.first, xHerb);
        BOOST_CHECK_EQUAL(targetPos.second, yHerb);
        map.clear();
        collection.deleteAllSubjects();
    }

    BOOST_AUTO_TEST_CASE( testAnimalMove )
    {
        AreaMap &map = AreaMap::getInstance();
        map.setSize(480, 640);
        //create Herbivore and setting target position:
        int xHerb(50), yHerb(50), maxLifeTime(10), viewSize(40);
        Coordinates targetPos = std::make_pair(70, 50);
        Herbivore *tHerb = new Herbivore(xHerb, yHerb, maxLifeTime, viewSize);
        map.insert(std::make_pair(xHerb, yHerb), tHerb);
        Target tar = FOOD;
        tHerb->oneLeapMove(map, targetPos, tar);
        int herbFinalX = xHerb + tHerb->getVelocity()*AREA_SIZE;
        int herbFinalY = yHerb;
        BOOST_CHECK_EQUAL(tHerb->getXPosition(), herbFinalX);
        BOOST_CHECK_EQUAL(tHerb->getYPosition(), herbFinalY);

        tar = ESCAPE; 
        tHerb->oneLeapMove(map, targetPos, tar);
        herbFinalX = xHerb - tHerb->getVelocity()*AREA_SIZE;
        herbFinalY = yHerb;
        BOOST_CHECK_EQUAL(tHerb->getXPosition(), herbFinalX);
        BOOST_CHECK_EQUAL(tHerb->getYPosition(), herbFinalY);
        delete tHerb;
    }

    BOOST_AUTO_TEST_CASE( testAnimalSleep )
    {
        int xHerb(50), yHerb(50), maxLifeTime(10), viewSize(40);
        Herbivore *tHerb = new Herbivore(xHerb, yHerb, maxLifeTime, viewSize);
        tHerb->setMaxEnergy(100);
        tHerb->setEnergy(50);
        int finalEnergy = tHerb->getEnergy() + PERCENT_OF_REGENERATION * tHerb->getMaxEnergy();
        tHerb->sleep();
        BOOST_CHECK_EQUAL(tHerb->getEnergy(), finalEnergy);
        delete tHerb;
    }

    BOOST_AUTO_TEST_CASE( testAnimalReproduce )
    {
        //create collection;
        int isReproductionPeriod = true;
        SubjectsCollection &collection = SubjectsCollection::getInstance();
        collection.setSizeOfAreaMap(WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE);
        //create two Herbivores
        int xHerb1(50), yHerb1(50), xHerb2(60), yHerb2(50), maxLifeTime(40), viewSize(40);
        Herbivore *tHerb1 = new Herbivore(xHerb1, yHerb1, maxLifeTime, viewSize);
        Herbivore *tHerb2 = new Herbivore(xHerb2, yHerb2, maxLifeTime, viewSize);
        collection.push(tHerb1);
        collection.push(tHerb2);
        int quantityBeforeReproduction = collection.getHerbivoresNumber();
        BOOST_CHECK_EQUAL(quantityBeforeReproduction, 2);
        //make test for reproduction two Herbivores
        collection.subjectsRound(isReproductionPeriod, maxLifeTime, viewSize);
        int quantityAfterReproduction = collection.getHerbivoresNumber();
        BOOST_CHECK_EQUAL(quantityAfterReproduction, 3);
        collection.deleteAllSubjects();
    }

    BOOST_AUTO_TEST_CASE( testUpdateParameters )
    {
        //create collection
        int isReproductionPeriod = false;
        SubjectsCollection &collection = SubjectsCollection::getInstance();
        collection.setSizeOfAreaMap(WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE);
        //create two herbivores
        int xHerb1(50), yHerb1(50), xHerb2(100), yHerb2(100), maxLifeTime(40), viewSize(40);
        Herbivore *tHerb1 = new Herbivore(xHerb1, yHerb1, maxLifeTime, viewSize);
        Herbivore *tHerb2 = new Herbivore(xHerb2, yHerb2, maxLifeTime, viewSize);
        collection.push(tHerb1);
        collection.push(tHerb2);

        collection.subjectsRound(isReproductionPeriod, maxLifeTime, viewSize);
        BOOST_CHECK(tHerb1->getEnergy() < tHerb1->getMaxEnergy());
        BOOST_CHECK(tHerb2->getFullness() < tHerb2->getMaxFullness());
        collection.deleteAllSubjects();
    }

    BOOST_AUTO_TEST_CASE( testHerbivoreEat )
    {
        //create collection
        int isReproductionPeriod = false;
        SubjectsCollection &collection = SubjectsCollection::getInstance();
        collection.setSizeOfAreaMap(WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE);
        //create herbivore
        int xHerb1(50), yHerb1(50), maxLifeTime(40), viewSize(40);
        Herbivore *tHerb1 = new Herbivore(xHerb1, yHerb1, maxLifeTime, viewSize);
        collection.push(tHerb1);
        //create Plant
        int xPlant(50), yPlant(60);
        TypicalPlant *tPlant = new TypicalPlant(xPlant, yPlant);
        collection.push(tPlant);
        //make herbivore hungry:
        tHerb1->setFullness(0.4*tHerb1->getMaxFullness()); 
        collection.subjectsRound(isReproductionPeriod, maxLifeTime, viewSize);
        BOOST_CHECK_EQUAL(collection.getPlantsNumber(), 0);
        collection.deleteAllSubjects();
    }

    BOOST_AUTO_TEST_CASE( testPredatorEat )
    {
        //create collection
        int isReproductionPeriod = false;
        SubjectsCollection &collection = SubjectsCollection::getInstance();
        collection.setSizeOfAreaMap(WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE);
        //create herbivore
        int xHerb1(50), yHerb1(50), maxLifeTime(40), viewSize(40);
        Herbivore *tHerb1 = new Herbivore(xHerb1, yHerb1, maxLifeTime, viewSize);
        collection.push(tHerb1);
        //create predator
        int xPred1(60), yPred1(50);
        Predator *tPred1 = new Predator(xPred1, yPred1, maxLifeTime, viewSize);
        collection.push(tPred1);
        //make predator hungry
        tPred1->setFullness(0.4*tPred1->getMaxFullness());
        collection.subjectsRound(isReproductionPeriod, maxLifeTime, viewSize);
        BOOST_CHECK_EQUAL(collection.getHerbivoresNumber(), 0);
        collection.deleteAllSubjects();
    }

BOOST_AUTO_TEST_SUITE_END();