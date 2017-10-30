#include<iostream>
#include <sstream>
using namespace std;

bool equal(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** rhs_elements,
	unsigned int rhs_rows,
	unsigned int rhs_columns)
{
    if((lhs_rows == rhs_rows)&&(lhs_columns == rhs_columns))
    {
        for(unsigned int i = 0; i < lhs_rows; ++i)
            for(unsigned int j = 0; j < lhs_columns; ++j){
                if(lhs_elements[i][j] == rhs_elements[i][j]) return true;
                else return false;
            }
    }
    else return false;
}

bool transpose( float ** lhs_elements,
unsigned int lhs_rows,
unsigned int lhs_columns,
float ** & result_elements,
unsigned int & result_rows,
unsigned int & result_columns )
{
    result_rows = lhs_rows;
    result_columns = lhs_columns;

    for(unsigned int i = 0; i < lhs_rows; ++i)
        for(unsigned int j = 0; j < lhs_columns; ++j){
            result_elements[i][j]=lhs_elements[j][i];
        }
    return true;
}

/*
bool truncate( float ** lhs_elements,
unsigned int lhs_rows,
unsigned int lhs_columns,
unsigned int new_rows,
unsigned int new_columns,
unsigned int start_row_index,
unsigned int start_colmn_index,
float ** & result_elements,
unsigned int & result_rows,
unsigned int & result_columns )
{
}
bool reverse( float ** lhs_elements,
unsigned int lhs_rows,
unsigned int lhs_columns,
float ** & result_elements,
unsigned int & result_rows,
unsigned int & result_columns )
{
}
*/
bool add(float ** lhs_elements,
         unsigned int lhs_rows,
         unsigned int lhs_columns,
         float ** rhs_elements,
         unsigned int rhs_rows,
         unsigned int rhs_columns,
         float ** & result_elements,
         unsigned int & result_rows,
         unsigned int & result_columns)
{
    if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
        for (int i = 0; i < lhs_rows; i++) {
            for (int j = 0; j < lhs_columns; j++) {
                result_elements[i][j] = lhs_elements[i][j] + rhs_elements[i][j];
            }
        }
        result_rows = lhs_rows;
        result_columns = lhs_columns;
        return true;
    }
    else return false;
}

bool sub(float ** lhs_elements,
         unsigned int lhs_rows,
         unsigned int lhs_columns,
         float ** rhs_elements,
         unsigned int rhs_rows,
         unsigned int rhs_columns,
         float ** & result_elements,
         unsigned int & result_rows,
         unsigned int & result_columns)
{
    if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
        for (int i = 0; i < lhs_rows; i++) {
            for (int j = 0; j < lhs_columns; j++) {
                result_elements[i][j] = lhs_elements[i][j] - rhs_elements[i][j];
            }
        }
        result_rows = lhs_rows;
        result_columns = lhs_columns;
        return true;
    }
    else return false;
}

bool multiply(float ** lhs_elements,
              unsigned int lhs_rows,
              unsigned int lhs_columns,
              float ** rhs_elements,
              unsigned int rhs_rows,
              unsigned int rhs_columns,
              float ** & result_elements,
              unsigned int & result_rows,
              unsigned int & result_columns)
{
    if (lhs_columns == rhs_rows) {
        for (int i = 0; i < lhs_rows; i++) {
            for (int j = 0; j < rhs_columns; j++){
                result_elements[i][j] = 0;
                for (int k = 0; k < lhs_columns; k++)
                    result_elements[i][j] += (lhs_elements[i][k] * rhs_elements[k][j]);
            }
        }
        return true;
    }
    else return false;
}

void destroy(float ** elements,
             unsigned int rows)
{
    for (unsigned int i = 0; i < rows; ++i) {
        delete[] elements[i];
    }
    delete[] elements;
}

auto input(istream & stream,
           float ** & result_elements,
           unsigned int & result_rows,
           unsigned int & result_columns) -> istream &
{
    char symbol;
    bool success = true;
    unsigned int rows;
    unsigned int columns;

    if (stream >> rows && stream >> symbol && symbol == ',' && stream >> columns);
    else {
        stream.setstate(std::ios::failbit);
        success = false;
        return stream;
    }

    string str;
    float ** elements;

    elements = new float *[rows];

    for (unsigned int i = 0; i < rows; ++i) {
        elements[i] = new float[columns];
        getline(stream, str);
        for (unsigned int j = 0; j < columns; ++j) {
            if(!(stream >> elements[i][j])) {
                stream.setstate(std::ios::failbit);
                success = false;
                return stream;
            }
        }
    }

    if (success) {
        result_elements = elements;
        result_rows = rows;
        result_columns = columns;
    }
    return stream;
}

auto output(std::ostream & stream,
            float ** elements,
            unsigned int rows,
            unsigned int columns)->std::ostream &
{
    stream << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            stream << elements[i][j]<<' ';
        }
        stream << endl;
    }
    return stream;
}

auto create(unsigned int rows,
            unsigned int columns,
            float filler = 0.0f) -> float **
{
    float ** elements = new float *[rows];
    for (unsigned int i = 0; i < rows; ++i) {
        elements[i] = new float[columns];
        for (unsigned int j = 0; j < columns; ++j) {
            elements[i][j] = filler;
        }
    }
    return elements;
}

int main() {
    float ** lhs_elements, ** rhs_elements, **result_elements;
    unsigned int lhs_rows, rhs_rows, result_rows;
    unsigned int lhs_columns, rhs_columns, result_columns;
    char op;

    if (!(input(cin, lhs_elements, lhs_rows, lhs_columns))) {
        cout << "An error has occured while reading input data.1\n";
        return 0;
    }

    cin >> op; cin.ignore();

    if(op!='T'&&op!='R') {

        if (!(input(cin, rhs_elements, rhs_rows, rhs_columns))) {
            cout << "An error has occured while reading input data.2\n";
            return 0;
        }

    }

    switch (op) {
        case '+': {
            if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
                result_elements = create(lhs_rows, lhs_columns);
                if (add(lhs_elements,
                        lhs_rows,
                        lhs_columns,
                        rhs_elements,
                        rhs_rows,
                        rhs_columns,
                        result_elements,
                        result_rows,
                        result_columns)) {
                    output(cout, result_elements, result_rows, result_columns);
                    destroy(lhs_elements,lhs_rows);
                    destroy(rhs_elements, rhs_rows);
                    destroy(result_elements, result_rows);
                }
            }
            else {
                cout << "An error has occured while reading input data.3\n";
                return 0;
            }
            break;
        }
        case '-': {
            if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
                result_elements = create(lhs_rows, lhs_columns);
                if (sub(lhs_elements,
                        lhs_rows,
                        lhs_columns,
                        rhs_elements,
                        rhs_rows,
                        rhs_columns,
                        result_elements,
                        result_rows,
                        result_columns)) {
                    output(cout, result_elements, result_rows, result_columns);
                    destroy(lhs_elements, lhs_rows);
                    destroy(rhs_elements, rhs_rows);
                    destroy(result_elements, result_rows);
                }

            }
            else {
                cout << "An error has occured while reading input data.3\n";
                return 0;
            }
            break;
        }
        case '*': {
            if (lhs_columns == rhs_rows) {
                result_elements = create(lhs_rows, rhs_columns);
                result_rows = lhs_rows;
                result_columns = rhs_columns;

                if (multiply(lhs_elements,
                             lhs_rows,
                             lhs_columns,
                             rhs_elements,
                             rhs_rows,
                             rhs_columns,
                             result_elements,
                             result_rows,
                             result_columns)) {

                    output(cout, result_elements, result_rows, result_columns);
                    destroy(lhs_elements, lhs_rows);
                    destroy(rhs_elements, rhs_rows);
                    destroy(result_elements, result_rows);
                }

            }
            else {
                cout << "An error has occured while reading input data.4\n";
                return 0;
            }
            break;
        }
        case 'T': {
            result_elements = create(lhs_columns, lhs_rows);
                if (transpose(lhs_elements,
                             lhs_rows,
                             lhs_columns,
                             result_elements,
                             result_rows,
                             result_columns)) {

                    output(cout, result_elements, result_rows, result_columns);
                    destroy(lhs_elements, lhs_rows);
                    destroy(result_elements, result_rows);
                }
            else {
                cout << "An error has occured while reading input data.\n";
                return 0;
            }
            break;
        }
    }






    return 0;
}
