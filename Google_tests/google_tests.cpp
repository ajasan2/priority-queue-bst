#include <gtest/gtest.h>
#include "priorityqueue.h"

TEST(Constructor, Int) {
    priorityqueue<int> pq;
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Constructor, Double) {
    priorityqueue<double> pq;
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Constructor, Char) {
    priorityqueue<char> pq;
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Constructor, String) {
    priorityqueue<string> pq;
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Constructor, Float) {
    priorityqueue<float> pq;
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Enqueue, OneNode) {
    priorityqueue<string> pq;
    pq.enqueue("Darwin", 2);
    ASSERT_EQ(pq.Size(), 1);
    ASSERT_EQ(pq.toString(), "2 value: Darwin\n");
}

TEST(Enqueue, SameValString) {
    priorityqueue<string> pq;
    pq.enqueue("Einstein", 0);
    ASSERT_EQ(pq.Size(), 1);
    pq.enqueue("Einstein", 2);
    ASSERT_EQ(pq.Size(), 2);
    ASSERT_EQ(pq.toString(), "0 value: Einstein\n2 value: Einstein\n");
}

TEST(Enqueue, SameValInt) {
    priorityqueue<int> pq;
    pq.enqueue(8, 0);
    ASSERT_EQ(pq.Size(), 1);
    pq.enqueue(8, 2);
    ASSERT_EQ(pq.Size(), 2);
    ASSERT_EQ(pq.toString(), "0 value: 8\n2 value: 8\n");
}

TEST(Enqueue, UniqueElements) {
    priorityqueue<long> pq;
    long value;
    int priority;
    pq.enqueue(5, 0);
    pq.enqueue(65, 6);
    pq.enqueue(45, 42);
    pq.enqueue(96, 28);
    pq.enqueue(67, 12);
    pq.enqueue(12, 34);
    pq.enqueue(42, 22);
    pq.enqueue(67, 18);
    ASSERT_EQ(pq.Size(), 8);
}

TEST(EnqueueDup, RootDuplicates) {
    priorityqueue<long> pq;
    pq.enqueue(44, 0);
    pq.enqueue(88, 0);
    ASSERT_EQ(pq.Size(), 2);
    ASSERT_EQ(pq.toString(), "0 value: 44\n0 value: 88\n");
}

TEST(EnqueueDup, OnOneNode) {
    priorityqueue<double> pq;
    pq.enqueue(42.458, 10);
    pq.enqueue(86.203, 6);
    pq.enqueue(35.219, 6);
    pq.enqueue(10.539, 6);
    ASSERT_EQ(pq.Size(), 4);
    ASSERT_EQ(pq.toString(), "6 value: 86.203\n6 value: 35.219\n"
                             "6 value: 10.539\n10 value: 42.458\n");
}

TEST(EnqueueDup, OnTwoNodes) {
    priorityqueue<double> pq;
    pq.enqueue(42.458, 10);
    pq.enqueue(86.203, 6);
    pq.enqueue(35.219, 6);
    pq.enqueue(23.504, 12);
    pq.enqueue(56.231, 12);
    ASSERT_EQ(pq.Size(), 5);
    ASSERT_EQ(pq.toString(), "6 value: 86.203\n6 value: 35.219\n"
                             "10 value: 42.458\n12 value: 23.504\n"
                             "12 value: 56.231\n");
}

TEST(EnqueueDup, OnMultiNodes) {
    priorityqueue<float> pq;
    float value;
    int priority;
    pq.enqueue(42.45, 44);
    pq.enqueue(55.86, 44);
    pq.enqueue(86.20,22);
    pq.enqueue(78.33, 22);
    pq.enqueue(35.21,11);
    pq.enqueue(23.50, 77);
    pq.enqueue(56.23, 77);
    pq.enqueue(95.65, 55);
    pq.enqueue(98.99, 55);
    pq.enqueue(92.54, 55);
    ASSERT_EQ(pq.Size(), 10);
    stringstream ss;
    string test_string = pq.toString();
    pq.begin();
    while(pq.next(value, priority)) {
        ss << priority << " value: " << value << endl;
    }
    ASSERT_EQ(ss.str(), test_string);
}

TEST(ToString, EmptyTree) {
    priorityqueue<string> pq;
    string test_string;
    ASSERT_EQ(pq.toString(), test_string);
}

TEST(ToString, SingleNode) {
    priorityqueue<float> pq;
    pq.enqueue(6.535, 28);
    ASSERT_EQ(pq.toString(), "28 value: 6.535\n");
}

TEST(ToString, MultipleOrdNodes) {
    priorityqueue<float> pq;
    pq.enqueue(87.5239, 4);
    pq.enqueue(73.1396, 6);
    pq.enqueue(90.0902, 10);
    string test_string = "4 value: 87.5239\n"
                         "6 value: 73.1396\n"
                         "10 value: 90.0902\n";
    ASSERT_EQ(pq.toString(), test_string);
}

TEST(ToString, MultipleUnordNodes) {
    priorityqueue<long> pq;
    pq.enqueue(1000, 12);
    pq.enqueue(2000, 34);
    pq.enqueue(3000, 22);
    pq.enqueue(4000, 10);
    string test_string = "10 value: 4000\n"
                         "12 value: 1000\n"
                         "22 value: 3000\n"
                         "34 value: 2000\n";
    ASSERT_EQ(pq.toString(), test_string);
}

TEST(ToStringDup, OnRootNode) {
    priorityqueue<char> pq;
    pq.enqueue('N', 12);
    pq.enqueue('B', 12);
    string test_string = "12 value: N\n"
                         "12 value: B\n";
    ASSERT_EQ(pq.toString(), test_string);
}

TEST(ToStringDup, OnOneRightNode) {
    priorityqueue<char> pq;
    pq.enqueue('N', 10);
    pq.enqueue('B', 14);
    pq.enqueue('P', 14);
    string test_string = "10 value: N\n"
                         "14 value: B\n"
                         "14 value: P\n";
    ASSERT_EQ(pq.toString(), test_string);
}

TEST(ToStringDup, OnTwoNodes) {
    priorityqueue<char> pq;
    pq.enqueue('N', 12);
    pq.enqueue('B', 8);
    pq.enqueue('C', 8);
    pq.enqueue('X', 20);
    pq.enqueue('G', 20);
    string test_string = "8 value: B\n"
                         "8 value: C\n"
                         "12 value: N\n"
                         "20 value: X\n"
                         "20 value: G\n";
    ASSERT_EQ(pq.toString(), test_string);
}

TEST(ToStringDup, OnAllNodes) {
    priorityqueue<float> pq;
    pq.enqueue(65.34, 32);
    pq.enqueue(124.52, 32);
    pq.enqueue(23.52, 22);
    pq.enqueue(816.23, 22);
    pq.enqueue(363.64, 46);
    pq.enqueue(977.94, 46);
    string test_string = "22 value: 23.52\n"
                         "22 value: 816.23\n"
                         "32 value: 65.34\n"
                         "32 value: 124.52\n"
                         "46 value: 363.64\n"
                         "46 value: 977.94\n";
    ASSERT_EQ(pq.toString(), test_string);
}

TEST(ToStringDup, OnMultiNodes) {
    priorityqueue<float> pq;
    pq.enqueue(65.34, 32);
    pq.enqueue(124.52, 22);
    pq.enqueue(23.52, 4);
    pq.enqueue(816.23, 44);
    pq.enqueue(234.12, 44);
    pq.enqueue(363.64, 38);
    pq.enqueue(87.23, 38);
    pq.enqueue(977.94, 50);
    pq.enqueue(888.23, 50);
    pq.enqueue(850.76, 50);
    string test_string = "4 value: 23.52\n22 value: 124.52\n"
                         "32 value: 65.34\n38 value: 363.64\n"
                         "38 value: 87.23\n44 value: 816.23\n"
                         "44 value: 234.12\n50 value: 977.94\n"
                         "50 value: 888.23\n50 value: 850.76\n";
    ASSERT_EQ(pq.toString(), test_string);
}

TEST(Clear, SingleNode) {
    priorityqueue<long> pq;
    pq.enqueue(999999, 44);
    pq.clear();
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Clear, MultipleOrdNodes) {
    priorityqueue<string> pq;
    pq.enqueue("Newton", 12);
    pq.enqueue("Franklin", 18);
    pq.enqueue("Copernicus", 20);
    pq.clear();
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Clear, MultipleUnordNodes) {
    priorityqueue<string> pq;
    pq.enqueue("Tesla", 42);
    pq.enqueue("Darwin", 6);
    pq.enqueue("Franklin", 18);
    pq.enqueue("Watson", 4);
    pq.clear();
    ASSERT_EQ(pq.Size(), 0);
}

TEST(AssignmentOp, FillEmptyTree) {
    priorityqueue<long> pq1, pq2;
    pq1.enqueue(12345678, 14);
    pq2 = pq1;
    ASSERT_EQ(pq2.Size(), 1);
    ASSERT_EQ(pq2.toString(), "14 value: 12345678\n");
}

TEST(AssignmentOp, OverwriteTree) {
    priorityqueue<int> pq1, pq2;
    pq1.enqueue(808, 14);
    pq2.enqueue(202, 30);
    pq2 = pq1;
    ASSERT_EQ(pq2.Size(), 1);
    ASSERT_EQ(pq2.toString(), "14 value: 808\n");
}

TEST(AssignmentOp, TreeVariation1) {
    priorityqueue<string> pq1, pq2;
    pq1.enqueue("Galilei", 14);
    pq1.enqueue("da Vinci", 32);
    pq1.enqueue("Celsius", 26);
    pq2.enqueue("Ampere", 40);
    pq2 = pq1;
    ASSERT_EQ(pq2.Size(), 3);
    string test_string = "14 value: Galilei\n"
                         "26 value: Celsius\n"
                         "32 value: da Vinci\n";
    ASSERT_EQ(pq2.toString(), test_string);
}

TEST(AssignmentOp, TreeVariation2) {
    priorityqueue<string> pq1, pq2;
    pq1.enqueue("da Vinci", 32);
    pq1.enqueue("Celsius", 26);
    pq2.enqueue("Ampere", 40);
    pq2.enqueue("Einstein", 4);
    pq2.enqueue("Tesla", 10);
    pq2 = pq1;
    ASSERT_EQ(pq2.Size(), 2);
    string test_string = "26 value: Celsius\n"
                         "32 value: da Vinci\n";
    ASSERT_EQ(pq2.toString(), test_string);
}

TEST(AssignmentOpDup, OnlyRootDuplicates) {
    priorityqueue<short> pq1, pq2;
    pq1.enqueue(1616, 14);
    pq1.enqueue(1818, 14);
    pq2 = pq1;
    ASSERT_EQ(pq2.Size(), 2);
    string test_string = "14 value: 1616\n"
                         "14 value: 1818\n";
    ASSERT_EQ(pq2.toString(), test_string);
}

TEST(AssignmentOpDup, OverwriteTreeWithoutDup) {
    priorityqueue<short> pq1, pq2;
    pq1.enqueue(4004, 14);
    pq2.enqueue(1001, 30);
    pq2.enqueue(9009, 30);
    pq1 = pq2;
    ASSERT_EQ(pq1.Size(), 2);
    string test_string = "30 value: 1001\n"
                         "30 value: 9009\n";
    ASSERT_EQ(pq2.toString(), test_string);
}

TEST(AssignmentOpDup, OverwriteTreeWithDup) {
    priorityqueue<char> pq1, pq2;
    pq1.enqueue('A', 14);
    pq1.enqueue('B', 14);
    pq1.enqueue('C', 10);
    pq2.enqueue('F', 14);
    pq2.enqueue('Q', 14);
    pq2.enqueue('R', 14);
    pq2.enqueue('V', 10);
    pq1 = pq2;
    ASSERT_EQ(pq1.Size(), 4);
    string test_string = "10 value: V\n"
                         "14 value: F\n"
                         "14 value: Q\n"
                         "14 value: R\n";
    ASSERT_EQ(pq2.toString(), test_string);
}

TEST(AssignmentOpDup, TreeVariation1) {
    priorityqueue<float> pq1, pq2;
    pq1.enqueue(44.444, 66);
    pq1.enqueue(55.555, 66);
    pq1.enqueue(66.666, 14);
    pq1.enqueue(77.777, 14);
    pq1.enqueue(88.888, 82);
    pq1.enqueue(99.999, 82);
    pq2.enqueue(55.555, 66);
    pq2.enqueue(66.666, 14);
    pq2.enqueue(88.888, 82);
    pq2 = pq1;
    ASSERT_EQ(pq2.Size(), 6);
    string test_string = "14 value: 66.666\n"
                         "14 value: 77.777\n"
                         "66 value: 44.444\n"
                         "66 value: 55.555\n"
                         "82 value: 88.888\n"
                         "82 value: 99.999\n";
    ASSERT_EQ(pq2.toString(), test_string);
}

TEST(Begin, EmptyTree) {
    priorityqueue<int> pq;
    int value, priority;
    pq.begin();
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(Next, OneNode) {
    priorityqueue<int> pq;
    int value, priority;
    pq.enqueue(11, 44);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 44);
    ASSERT_EQ(value, 11);
    ASSERT_EQ(pq.next(value, priority), false);
}


TEST(Next, TwoNodeLeft) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Linnaeus", 44);
    pq.enqueue("Galilei", 14);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 14);
    ASSERT_EQ(value, "Galilei");
    pq.next(value, priority);
    ASSERT_EQ(priority, 44);
    ASSERT_EQ(value, "Linnaeus");
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(Next, TwoNodeRight) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Watson", 4);
    pq.enqueue("Celsius", 26);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 4);
    ASSERT_EQ(value, "Watson");
    pq.next(value, priority);
    ASSERT_EQ(priority, 26);
    ASSERT_EQ(value, "Celsius");
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(Next, ThreeNodesBalanced) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Tesla", 10);
    pq.enqueue("Watson", 4);
    pq.enqueue("Celsius", 26);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 4);
    ASSERT_EQ(value, "Watson");
    pq.next(value, priority);
    ASSERT_EQ(priority, 10);
    ASSERT_EQ(value, "Tesla");
    pq.next(value, priority);
    ASSERT_EQ(priority, 26);
    ASSERT_EQ(value, "Celsius");
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(Next, ThreeLeftOrdered) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Faraday", 28);
    pq.enqueue("Newton", 12);
    pq.enqueue("Edison", 10);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 10);
    ASSERT_EQ(value, "Edison");
    pq.next(value, priority);
    ASSERT_EQ(priority, 12);
    ASSERT_EQ(value, "Newton");
    pq.next(value, priority);
    ASSERT_EQ(priority, 28);
    ASSERT_EQ(value, "Faraday");
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(Next, ThreeLeftUnordered) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Faraday", 28);
    pq.enqueue("Newton", 12);
    pq.enqueue("Edison", 20);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 12);
    ASSERT_EQ(value, "Newton");
    pq.next(value, priority);
    ASSERT_EQ(priority, 20);
    ASSERT_EQ(value, "Edison");
    pq.next(value, priority);
    ASSERT_EQ(priority, 28);
    ASSERT_EQ(value, "Faraday");
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(Next, ThreeRightOrdered) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Newton", 12);
    pq.enqueue("Fleming", 30);
    pq.enqueue("da Vinci", 32);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 12);
    ASSERT_EQ(value, "Newton");
    pq.next(value, priority);
    ASSERT_EQ(priority, 30);
    ASSERT_EQ(value, "Fleming");
    pq.next(value, priority);
    ASSERT_EQ(priority, 32);
    ASSERT_EQ(value, "da Vinci");
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(Next, ThreeRightUnordered) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Watson", 4);
    pq.enqueue("Celsius", 26);
    pq.enqueue("Curie", 22);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 4);
    ASSERT_EQ(value, "Watson");
    pq.next(value, priority);
    ASSERT_EQ(priority, 22);
    ASSERT_EQ(value, "Curie");
    pq.next(value, priority);
    ASSERT_EQ(priority, 26);
    ASSERT_EQ(value, "Celsius");
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(Next, MultiBranchedLeftSubtree1) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Tesla", 42);
    pq.enqueue("Fleming", 30);
    pq.enqueue("da Vinci", 32);
    pq.enqueue("Curie", 22);
    pq.enqueue("Newton", 12);
    pq.enqueue("Bohr", 34);

//                        42
//                  30
//            22          32
//      12                      34

    stringstream ss;
    string test_string = pq.toString();
    pq.begin();
    while(pq.next(value, priority)) {
        ss << priority << " value: " << value << endl;
    }
    ASSERT_EQ(ss.str(), test_string);
}

TEST(Next, MultiBranchedLeftSubtree2) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Tesla", 42);
    pq.enqueue("Fleming", 30);
    pq.enqueue("da Vinci", 32);
    pq.enqueue("Curie", 22);
    pq.enqueue("Newton", 12);
    pq.enqueue("Bohr", 34);
    pq.enqueue("Franklin", 28);

//                        42
//                  30
//            22          32
//      12          28          34

    stringstream ss;
    string test_string = pq.toString();
    pq.begin();
    while(pq.next(value, priority)) {
        ss << priority << " value: " << value << endl;
    }
    ASSERT_EQ(ss.str(), test_string);
}

TEST(Next, MultiBranchedLRightSubtree1) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Edison", 14);
    pq.enqueue("Celsius", 40);
    pq.enqueue("Ampere", 28);
    pq.enqueue("Darwin", 22);
    pq.enqueue("Copernicus", 48);
    pq.enqueue("Bohr", 54);

//            14
//                  40
//            28          48
//      22                      54

    stringstream ss;
    string test_string = pq.toString();
    pq.begin();
    while(pq.next(value, priority)) {
        ss << priority << " value: " << value << endl;
    }
    ASSERT_EQ(ss.str(), test_string);
}

TEST(Next, MultiBranchedLRightSubtree2) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Edison", 14);
    pq.enqueue("Celsius", 40);
    pq.enqueue("Ampere", 28);
    pq.enqueue("Darwin", 22);
    pq.enqueue("Copernicus", 48);
    pq.enqueue("Bohr", 54);
    pq.enqueue("Linnaeus", 34);

//            14
//                  40
//            28          48
//      22          34          54

    stringstream ss;
    string test_string = pq.toString();
    pq.begin();
    while(pq.next(value, priority)) {
        ss << priority << " value: " << value << endl;
    }
    ASSERT_EQ(ss.str(), test_string);
}

TEST(Next, BigTreeVariation1) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Tesla", 42);
    pq.enqueue("Fleming", 30);
    pq.enqueue("Curie", 22);
    pq.enqueue("Newton", 12);
    pq.enqueue("Edison", 14);
    pq.enqueue("Franklin", 24);
    pq.enqueue("Ampere", 28);
    pq.enqueue("Bohr", 34);
    pq.enqueue("da Vinci", 44);
    pq.enqueue("Celsius", 40);
    pq.enqueue("Linnaeus", 50);
    pq.enqueue("Copernicus", 48);
    pq.enqueue("Darwin", 46);
    pq.enqueue("Einstein", 60);
    pq.enqueue("Bohr", 54);

//                            42
//                    30              44
//              22         34    40         50
//        12          24              48          60
//              14         28    46         54

    string test_string = pq.toString();
    stringstream nextString;
    pq.begin();
    while (pq.next(value, priority)) {
      nextString << priority << " value: " << value << endl;
    }
    ASSERT_EQ(nextString.str(), test_string);
}

TEST(Next, BigTreeVariation2) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Tesla", 42);
    pq.enqueue("Fleming", 30);
    pq.enqueue("Curie", 22);
    pq.enqueue("Newton", 12);
    pq.enqueue("Edison", 14);
    pq.enqueue("Ampere", 16);
    pq.enqueue("Bohr", 18);
    pq.enqueue("da Vinci", 46);
    pq.enqueue("Linnaeus", 50);
    pq.enqueue("Einstein", 60);
    pq.enqueue("Lovelace", 56);
    pq.enqueue("Copernicus", 54);
    pq.enqueue("Turing", 52);

//                             42
//                     30               46
//               22                           50
//         12                                       60
//               14                           56
//                     16               54
//                          18    52


    string test_string = pq.toString();
    stringstream nextString;
    pq.begin();
    while (pq.next(value, priority)) {
        nextString << priority << " value: " << value << endl;
    }
    ASSERT_EQ(nextString.str(), test_string);
}

TEST(NextDup, OnlyRootDuplicate) {
    priorityqueue<char> pq;
    char value;
    int priority;
    pq.enqueue('L', 44);
    pq.enqueue('M', 44);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 44);
    ASSERT_EQ(value, 'L');
    pq.next(value, priority);
    ASSERT_EQ(priority, 44);
    ASSERT_EQ(value, 'M');
    ASSERT_EQ(pq.next(value, priority), false);
}


TEST(NextDup, LeftTwoNodesOneDup) {
    priorityqueue<char> pq;
    char value;
    int priority;
    pq.enqueue('G', 58);
    pq.enqueue('H', 22);
    pq.enqueue('I', 22);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 22);
    ASSERT_EQ(value, 'H');
    pq.next(value, priority);
    ASSERT_EQ(priority, 22);
    ASSERT_EQ(value, 'I');
    pq.next(value, priority);
    ASSERT_EQ(priority, 58);
    ASSERT_EQ(value, 'G');
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(NextDup, RightTwoNodesOneDup) {
    priorityqueue<double> pq;
    double value;
    int priority;
    pq.enqueue(2.3415, 1);
    pq.enqueue(5.2325, 2);
    pq.enqueue(7.1209, 2);
    pq.begin();
    pq.next(value, priority);
    ASSERT_EQ(priority, 1);
    ASSERT_EQ(value, 2.3415);
    pq.next(value, priority);
    ASSERT_EQ(priority, 2);
    ASSERT_EQ(value, 5.2325);
    pq.next(value, priority);
    ASSERT_EQ(priority, 2);
    ASSERT_EQ(value, 7.1209);
    ASSERT_EQ(pq.next(value, priority), false);
}

TEST(NextDup, ThreeNodesBalanced) {
    priorityqueue<double> pq;
    double value;
    int priority;
    pq.enqueue(20.20, 2);
    pq.enqueue(10.10, 1);
    pq.enqueue(30.30, 3);
    pq.enqueue(20.20, 2);
    pq.enqueue(10.10, 1);
    pq.enqueue(30.30, 3);

    string test_string = pq.toString();
    stringstream nextString;
    pq.begin();
    while (pq.next(value, priority)) {
        nextString << priority << " value: " << value << endl;
    }
    ASSERT_EQ(nextString.str(), test_string);
}

TEST(Dequeue, EmptyTree) {
    priorityqueue<string> pq;
    ASSERT_EQ(pq.dequeue(), "");
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Dequeue, OneNode) {
    priorityqueue<string> pq;
    pq.enqueue("Newton", 12);
    ASSERT_EQ(pq.dequeue(), "Newton");
    ASSERT_EQ(pq.dequeue(), "");
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Dequeue, TwoNodes) {
    priorityqueue<string> pq;
    pq.enqueue("Newton", 12);
    pq.enqueue("Celsius", 40);
    ASSERT_EQ(pq.dequeue(), "Newton");
    ASSERT_EQ(pq.dequeue(), "Celsius");
    ASSERT_EQ(pq.dequeue(), "");
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Dequeue, ThreeNodes) {
    priorityqueue<string> pq;
    pq.enqueue("Newton", 12);
    pq.enqueue("Celsius", 40);
    pq.enqueue("Edison", 14);
    ASSERT_EQ(pq.dequeue(), "Newton");
    ASSERT_EQ(pq.dequeue(), "Edison");
    ASSERT_EQ(pq.dequeue(), "Celsius");
    ASSERT_EQ(pq.dequeue(), "");
    ASSERT_EQ(pq.Size(), 0);
}

TEST(DequeueDouble, ThreeNodes) {
    priorityqueue<double> pq;
    pq.enqueue(39.4, 12);
    pq.enqueue(40.2, 40);
    pq.enqueue(42.4, 14);
    ASSERT_EQ(pq.dequeue(), 39.4);
    ASSERT_EQ(pq.dequeue(), 42.4);
    ASSERT_EQ(pq.dequeue(), 40.2);
    ASSERT_EQ(pq.dequeue(), 0);
    ASSERT_EQ(pq.Size(), 0);
}

TEST(DequeueDouble, MultipleNodes) {
    priorityqueue<double> pq;
    double value;
    pq.enqueue(39.4, 12);
    pq.enqueue(40.2, 40);
    pq.enqueue(42.4, 14);
    pq.enqueue(45.1, 22);
    pq.enqueue(44.4, 5);
    pq.enqueue(44.9, 8);

    //                  12
    //          5               40
    //              8      14
    //                          22
    stringstream ss;
    for (int i = 0; i < 6; i++) {
        ss << pq.dequeue() << " ";
    }
    string test_string = "44.4 44.9 39.4 42.4 45.1 40.2 ";
    ASSERT_EQ(ss.str(), test_string);
    ASSERT_EQ(pq.Size(), 0);
}

TEST(DequeueChar, MultipleNodes) {
    priorityqueue<char> pq;
    char value;
    pq.enqueue('M', 40);
    pq.enqueue('F', 60);
    pq.enqueue('S', 50);
    pq.enqueue('A', 80);
    pq.enqueue('L', 70);
    pq.enqueue('V', 100);
    pq.enqueue('P', 20);
    pq.enqueue('B', 30);
    pq.enqueue('O', 10);

    //                     40
    //            20                 60
    //      10         30     50           80
    //                               70         100
    stringstream ss;
    for (int i = 0; i < 9; i++) {
        ss << pq.dequeue();
    }
    string test_string = "OPBMSFLAV";
    ASSERT_EQ(ss.str(), test_string);
    ASSERT_EQ(pq.Size(), 0);
}

TEST(DequeueDup, OnlyRootDuplicates) {
    priorityqueue<string> pq;
    pq.enqueue("Newton", 12);
    pq.enqueue("Celsius", 12);
    ASSERT_EQ(pq.dequeue(), "Newton");
    ASSERT_EQ(pq.dequeue(), "Celsius");
    ASSERT_EQ(pq.dequeue(), "");
    ASSERT_EQ(pq.Size(), 0);
}

TEST(DequeueDup, TwoNodesLeft1) {
    priorityqueue<string> pq;
    pq.enqueue("Newton", 12);
    pq.enqueue("Celsius", 6);
    pq.enqueue("Edison", 12);
    ASSERT_EQ(pq.dequeue(), "Celsius");
    ASSERT_EQ(pq.dequeue(), "Newton");
    ASSERT_EQ(pq.dequeue(), "Edison");
    ASSERT_EQ(pq.dequeue(), "");
    ASSERT_EQ(pq.Size(), 0);
}

TEST(DequeueDup, TwoNodesLeft2) {
    priorityqueue<string> pq;
    pq.enqueue("Newton", 12);
    pq.enqueue("Celsius", 40);
    pq.enqueue("Edison", 40);
    ASSERT_EQ(pq.dequeue(), "Newton");
    ASSERT_EQ(pq.dequeue(), "Celsius");
    ASSERT_EQ(pq.dequeue(), "Edison");
    ASSERT_EQ(pq.dequeue(), "");
    ASSERT_EQ(pq.Size(), 0);
}

TEST(DequeueDup, TwoNodesRight1) {
    priorityqueue<char> pq;
    pq.enqueue('a', 20);
    pq.enqueue('b', 20);
    pq.enqueue('e', 80);
    ASSERT_EQ(pq.dequeue(), 'a');
    ASSERT_EQ(pq.dequeue(), 'b');
    ASSERT_EQ(pq.dequeue(), 'e');
    ASSERT_EQ(pq.Size(), 0);
}

TEST(DequeueDup, TwoNodesRight2) {
    priorityqueue<char> pq;
    pq.enqueue('l', 20);
    pq.enqueue('m', 80);
    pq.enqueue('n', 80);
    ASSERT_EQ(pq.dequeue(), 'l');
    ASSERT_EQ(pq.dequeue(), 'm');
    ASSERT_EQ(pq.dequeue(), 'n');
    ASSERT_EQ(pq.Size(), 0);
}

TEST(DequeueDup, ThreeNodesWithDup) {
    priorityqueue<char> pq;
    pq.enqueue('c', 40);
    pq.enqueue('d', 40);
    pq.enqueue('a', 20);
    pq.enqueue('b', 20);
    pq.enqueue('e', 80);
    pq.enqueue('f', 80);
    stringstream ss;
    for (int i = 0; i < 6; i++) {
        ss << pq.dequeue();
    }
    string test_string = "abcdef";
    ASSERT_EQ(ss.str(), test_string);
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Peek, OneNode) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Fleming", 30);
    ASSERT_EQ(pq.peek(), "Fleming");
    ASSERT_EQ(pq.Size(), 1);
}

TEST(Peek, TwoNode) {
    priorityqueue<string> pq;
    string value;
    int priority;
    pq.enqueue("Fleming", 30);
    pq.enqueue("Bohr", 34);
    ASSERT_EQ(pq.peek(), "Fleming");
    ASSERT_EQ(pq.Size(), 2);
    pq.dequeue();
    ASSERT_EQ(pq.peek(), "Bohr");
    ASSERT_EQ(pq.Size(), 1);
    pq.dequeue();
    ASSERT_EQ(pq.peek(), "");
    ASSERT_EQ(pq.Size(), 0);
}

TEST(PeekInt, ThreeNode) {
    priorityqueue<int> pq;
    int value, priority;
    pq.enqueue(2, 30);
    pq.enqueue(6, 34);
    pq.enqueue(10, 28);
    ASSERT_EQ(pq.peek(), 10);
    ASSERT_EQ(pq.Size(), 3);
    pq.dequeue();
    ASSERT_EQ(pq.peek(), 2);
    ASSERT_EQ(pq.Size(), 2);
    pq.dequeue();
    ASSERT_EQ(pq.peek(), 6);
    ASSERT_EQ(pq.Size(), 1);
}

TEST(PeekInt, MultipleNode) {
    priorityqueue<int> pq;
    int value, priority;
    pq.enqueue(2, 30);
    pq.enqueue(6, 34);
    pq.enqueue(10, 28);
    pq.enqueue(14, 20);
    pq.enqueue(22, 40);

    vector<int> order = {14, 10, 2, 6, 22};

    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(pq.peek(), order[i]);
        ASSERT_EQ(pq.Size(), 5 - i);
        pq.dequeue();
    }
    ASSERT_EQ(pq.Size(), 0);
}

TEST(Equal, EmptyTree) {
    priorityqueue<int> pq1, pq2;
    ASSERT_EQ(pq1 == pq2, true);
}

TEST(Equal, UnequalSize) {
    priorityqueue<int> pq1, pq2;
    ASSERT_EQ(pq1 == pq2, true);
    pq1.enqueue(50, 50);
    ASSERT_EQ(pq1 == pq2, false);
}

TEST(Equal, UnequalVal) {
    priorityqueue<float> pq1, pq2;
    ASSERT_EQ(pq1 == pq2, true);
    pq1.enqueue(39.2812733, 24);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue(44.6893481, 24);
    ASSERT_EQ(pq1 == pq2, false);
}

TEST(Equal, ExtraNode) {
    priorityqueue<float> pq1, pq2;
    ASSERT_EQ(pq1 == pq2, true);
    pq1.enqueue(39.2812733, 24);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue(39.2812733, 24);
    pq2.enqueue(84.1230909, 30);
    ASSERT_EQ(pq1 == pq2, false);
}

TEST(Equal, DifferentShape) {
    priorityqueue<float> pq1, pq2;
    ASSERT_EQ(pq1 == pq2, true);
    pq1.enqueue(39.2812733, 24);
    pq1.enqueue(84.1230909, 20);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue(39.2812733, 24);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue(84.1230909, 30);
    ASSERT_EQ(pq1 == pq2, false);
}

TEST(Equal, BigTreeVariation1) {
    priorityqueue<char> pq1, pq2;
    pq1.enqueue('A', 100);
    pq1.enqueue('B', 50);
    pq1.enqueue('C', 150);
    pq1.enqueue('D', 25);
    pq1.enqueue('E', 75);
    pq1.enqueue('F', 10);

    pq2.enqueue('A', 100);
    pq2.enqueue('B', 50);
    pq2.enqueue('C', 150);
    pq2.enqueue('D', 25);
    pq2.enqueue('E', 75);
    pq2.enqueue('F', 10);
    ASSERT_EQ(pq1 == pq2, true);

    pq2.enqueue('F', 200);
    ASSERT_EQ(pq1 == pq2, false);
}

TEST(Equal, BigTreeVariation2) {
    priorityqueue<char> pq1, pq2;
    pq1.enqueue('Z', 100);
    pq1.enqueue('Y', 50);
    pq1.enqueue('X', 200);
    pq1.enqueue('W', 150);
    pq1.enqueue('V', 125);
    pq1.enqueue('U', 25);
    pq1.enqueue('T', 5);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue('Z', 100);
    pq2.enqueue('Y', 50);
    pq2.enqueue('X', 200);
    pq2.enqueue('W', 150);
    pq2.enqueue('V', 125);
    pq2.enqueue('U', 25);
    pq2.enqueue('T', 5);
    ASSERT_EQ(pq1 == pq2, true);
}

TEST(EqualDup, OnlyRootDuplicates) {
    priorityqueue<int> pq1, pq2;
    pq1.enqueue(46, 64);
    pq1.enqueue(86, 64);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue(46, 64);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue(86, 64);
    ASSERT_EQ(pq1 == pq2, true);
}

TEST(EqualDup, DuplicatesWrongOrder) {
    priorityqueue<int> pq1, pq2;
    ASSERT_EQ(pq1 == pq2, true);
    pq1.enqueue(50, 50);
    pq1.enqueue(100, 50);
    pq1.enqueue(150, 50);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue(50, 50);
    pq2.enqueue(150, 50);
    pq2.enqueue(100, 50);
    ASSERT_EQ(pq1 == pq2, false);
}

TEST(EqualDup, ExtraDuplicate) {
    priorityqueue<float> pq1, pq2;
    ASSERT_EQ(pq1 == pq2, true);
    pq1.enqueue(39.2812733, 24);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue(39.2812733, 24);
    ASSERT_EQ(pq1 == pq2, true);
    pq1.enqueue(44.6893481, 24);
    ASSERT_EQ(pq1 == pq2, false);
}

TEST(EqualDup, MultipleNodes) {
    priorityqueue<float> pq1, pq2;
    ASSERT_EQ(pq1 == pq2, true);
    pq1.enqueue(43.1247653, 24);
    ASSERT_EQ(pq1 == pq2, false);
    pq2.enqueue(43.1247653, 24);
    ASSERT_EQ(pq1 == pq2, true);
    pq1.enqueue(84.1230909, 30);
    pq1.enqueue(64.5092390, 64);
    pq1.enqueue(85.1238957, 54);
    pq2.enqueue(84.1230909, 30);
    pq2.enqueue(76.3239213, 64);
    ASSERT_EQ(pq1 == pq2, false);
}

TEST(MultipleFunctions, Test1) {
    priorityqueue<char> pq1, pq2;
    char value;
    int priority;
    ASSERT_EQ(pq1.peek(), '\0');
    pq1.enqueue('A', 005);
    ASSERT_EQ(pq1.dequeue(), 'A');
    ASSERT_EQ(pq1.Size(), 0);
    pq1.enqueue('Z', 500);
    pq2 = pq1;
    ASSERT_EQ(pq2.peek(), 'Z');
    pq2.enqueue('N', 200);
    ASSERT_EQ(pq1 == pq2, false);
    pq1 = pq2;
    pq1.begin();
    pq2.next(value, priority);
    pq2.next(value, priority);
    ASSERT_EQ(value, 'Z');
    ASSERT_EQ(priority, 500);
    pq2.clear();
    ASSERT_EQ(pq2.Size(), 0);
}

TEST(MultipleFunctions, Test2) {
    priorityqueue<short> pq1, pq2;
    short value;
    int priority;
    pq1.enqueue(20, 1);
    ASSERT_EQ(pq1 == pq2, false);
    pq1.enqueue(10, 1);
    pq2.enqueue(10, 1);
    ASSERT_EQ(pq1 == pq2, false);
    pq2 = pq1;
    ASSERT_EQ(pq2.Size(), 2);
    pq2.begin();
    pq2.next(value, priority);
    ASSERT_EQ(value, 20);
    ASSERT_EQ(priority, 1);
    pq1.clear();
    ASSERT_EQ(pq1.Size(), 0);
    ASSERT_EQ(pq1.peek(), false);
    ASSERT_EQ(pq1.dequeue(), false);
    pq2.enqueue(4, 4);
    pq2.enqueue(2, 4);
    pq2.next(value, priority);
    pq2.next(value, priority);
    ASSERT_EQ(value, 4);
    ASSERT_EQ(priority, 4);
    ASSERT_EQ(pq2.dequeue(), 20);
    ASSERT_EQ(pq2.peek(), 10);
}