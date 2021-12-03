#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[])
{
	    int x = atoi(argv[1]);
		int y = atoi(argv[2]);

	    int** array = new int*[x];
				    for(int i = 0; i < x; i++)
						        array[i] = new int[y];
					    for(int i = 0; i < y; i++)
						{
							for(int j = 0; j < x; j++)
							{
								array[i][j] = 0;
						   }
						}

						 for(int i = 0; i < y; i++)
						{
							for(int j = 0; j < x; j++)
								{
								cout << array[i][j] << " ";
																			        }

								 cout << endl;
						}
					for(int i = 0; i < x; i++)
						    {
							        delete array[y];
							    }
					

							    delete[] array;
								    return 0;
}

