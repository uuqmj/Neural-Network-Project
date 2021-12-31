#include "input.hpp"

std::vector<std::vector<std::vector<double>>> get_training_Data()
{

    std::ifstream data_training;
    data_training.open("data/fashion_mnist_train_vectors.csv");
    if (!data_training.is_open())
        throw std::runtime_error("Could not open file");

    std::string line, val;                                   /* string for line & value */
    std::vector<std::vector<double>> vector_training_data_1; //vector for spliting up the training data set
    std::vector<std::vector<double>> vector_training_data_2; //vector for spliting up the training data set
    int counter = 0;                                         // counter for counting the lines and knowing the split of point

    int sum_vector_1 = 0;
    int sum_vector_2 = 0;

    while (std::getline(data_training, line))
    {                                     /* read each line */
        std::vector<double> row_vector_1; /* row vector 1 for first array*/
        std::vector<double> row_vector_2; /* row vector 2 for second array*/
        std::stringstream s(line);        /* stringstream s line */

        if (counter < 45000)
        {
            while (getline(s, val, ','))
            {                                           /* get each value (',' delimited) */
                row_vector_1.push_back(std::stoi(val)); /* add to row vector */
                                                        //	std:cout << val << " ";
                sum_vector_1 += std::stoi(val);
            }
            vector_training_data_1.push_back(row_vector_1); /* add row vector to array 1 */
        }
        else if (counter >= 45000 && counter < 60000)
        {
            while (getline(s, val, ','))
            {                                           /* get each value (',' delimited) */
                row_vector_2.push_back(std::stoi(val)); /* add to row vector */
                //	std:cout << val << " ";
                sum_vector_2 += std::stoi(val);
            }
            vector_training_data_2.push_back(row_vector_2); /* add row vector to array 2*/
        }

        counter++;
    }

    double mean_vector_1 = (double)sum_vector_1 / 45000.0;

    double mean_vector_2 = (double)sum_vector_2 / 25000.0;

    double stddev_vector_1 = stddev(vector_training_data_1, mean_vector_1);
    double stddev_vector_2 = stddev(vector_training_data_2, mean_vector_2);

    vector_training_data_1 = standartize(vector_training_data_1, stddev_vector_1, mean_vector_1);
    vector_training_data_2 = standartize(vector_training_data_2, stddev_vector_2, mean_vector_2);

    return {vector_training_data_1, vector_training_data_2};
}

std::vector<std::vector<std::vector<int>>> get_labeled_training_Data()
{

    std::ifstream data_labeled;
    data_labeled.open("data/fashion_mnist_train_labels.csv");
    if (!data_labeled.is_open())
        throw std::runtime_error("Could not open file");

    std::string line, val;                                                      // string for line & value
    std::vector<std::vector<int>> vector_labeled_data_1, vector_labeled_data_2; //vector of vector<int>
    int counter = 0;

    while (std::getline(data_labeled, line))
    {                              // read each line
        std::vector<int> v;        // row vector v
        std::stringstream s(line); // stringstream line
        std::cout << "\n";

        if (counter < 45000)
        {                                   // test data set -> get data row up to 4500
            std::vector<int> help_vector_1; // Define help vector for temporal storage
            for (int i = 0; i <= 9; i++)
            {

                getline(s, val, ','); // get each value (',' delimited)
                int k;                //Hilfsvariable
                k = std::stoi(val);
                if (k == i)
                {
                    help_vector_1.push_back(1);
                }
                else
                {
                    help_vector_1.push_back(0);
                }
            }
            vector_labeled_data_1.push_back(help_vector_1);
        }

        else if (counter >= 45000 && counter < 60000)
        {                                   // test data set -> get data row between 4500 and 6000
            std::vector<int> help_vector_2; // Define help vector for temporal storage
            for (int i = 0; i <= 9; i++)
            {

                getline(s, val, ',');   // get each value (',' delimited)
                int j = std::stoi(val); //Hilfsvariable
                if (j == i)
                {
                    help_vector_2.push_back(1);
                }
                else
                    help_vector_2.push_back(0);
            }
            vector_labeled_data_2.push_back(help_vector_2); // Push back help vector for temporal storage to orinal vector
        }
        counter++;
    }

    return {vector_labeled_data_1, vector_labeled_data_2};
}

std::vector<std::vector<double>> get_test_Data()
{

    std::ifstream data_test;
    data_test.open("data/fashion_mnist_test_vectors.csv");
    if (!data_test.is_open())
        throw std::runtime_error("Could not open file");

    std::string line, val;                             /* string for line & value */
    std::vector<std::vector<double>> vector_test_data; //vector for spliting up the training data set
    //vector for spliting up the training data set

    int sum = 0;

    while (std::getline(data_test, line))
    {                                     /* read each line */
        std::vector<double> row_vector_1; /* row vector 1 for first array*/
        std::stringstream s(line);        /* stringstream s line */

        while (getline(s, val, ','))
        {                                           /* get each value (',' delimited) */
            row_vector_1.push_back(std::stoi(val)); /* add to row vector */
            //	std:cout << val << " ";

            sum += std::stoi(val);
        }

        vector_test_data.push_back(row_vector_1); /* add row vector to array 1 */
                                                  /* add row vector to array 2*/
    }

    double mean = (double)sum / 10000;
    double stddev_test = stddev(vector_test_data, mean);
    vector_test_data = standartize(vector_test_data, mean, stddev_test);
    return vector_test_data;
}

std::vector<std::vector<int>> get_labeled_test_data()
{

    std::ifstream test_data_labeled;
    test_data_labeled.open("data/fashion_mnist_test_labels.csv");
    if (!test_data_labeled.is_open())
        throw std::runtime_error("Could not open file");

    std::string line, val;                                                      // string for line & value
    std::vector<std::vector<int>> vector_labeled_data_1, vector_labeled_data_2; //vector of vector<int>

    while (std::getline(test_data_labeled, line))
    {                              // read each line
        std::vector<int> v;        // row vector v
        std::stringstream s(line); // stringstream line
        std::cout << "\n";
        // test data set -> get data row up to 45000
        std::vector<int> help_vector_1; // Define help vector for temporal storage
        for (int i = 0; i <= 9; i++)
        {

            getline(s, val, ','); // get each value (',' delimited)
            int k;                //Hilfsvariable
            k = std::stoi(val);
            if (k == i)
            {
                help_vector_1.push_back(1);
            }
            else
            {
                help_vector_1.push_back(0);
            }
        }
        vector_labeled_data_1.push_back(help_vector_1);
    }

    return {
        vector_labeled_data_1,
    };
}

void print_training_data_in_csv(std::vector<int> training_results_last_layer)
{

    std::ofstream myFile_training_results;
    myFile_training_results.open("trainPredictions.csv");
    for (int i = 0; i < (int)training_results_last_layer.size(); i++)
    {

        myFile_training_results << training_results_last_layer[i] << std::endl;

        //int output_class = index_of_maximum(output);
    }
}

void print_testing_data_in_csv(std::vector<int> testing_results_last_layer)
{

    std::ofstream myFile_testing_results;
    myFile_testing_results.open("actualTestPredictions.csv");

    for (int i = 0; i < (int)testing_results_last_layer.size(); i++)
    {

        myFile_testing_results << testing_results_last_layer[i] << std::endl;

        //int output_class = index_of_maximum(output);
    }
}
