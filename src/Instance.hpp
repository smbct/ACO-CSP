/**
 * \file Instance.hpp
 * \file declaration of an Instance class
 */

#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <string>
#include <vector>
#include <map>

/**
 * \class Instance
 * \brief manage an instance of the csp problem
 */
class Instance {

    public:

        /**
         * \brief default constructor
         */
        Instance();

        /**
         * \brief load a instance of the CSP problem
         * \param fileName the name of the file
         * \return true iff the instance has been opened without troubles
         */
        bool load(std::string fileName);


        /**
         * \brief display the instance
         */
        void display();

    private:

        int _nChar; // number of characters in the alphabet
        std::map<char, int> _charInd; // index of the characters
        std::vector<char> _invMap; // invers map, find the character from the index

        int _nString; // number of strings
        int _stringLength;
        std::vector<std::vector<int> > _stringList; // list of the strings


};

#endif
