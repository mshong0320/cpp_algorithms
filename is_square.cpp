// suppose that you have 4 arbitrary points on a 2d plane
// coordinates are integers, abs(Xi, Yi) <= 1000000
// question: do they form a square?

/*!
   @brief is_square - Proprietary and confidential
   @author Minsung C. Hong

   All Rights Reserved
   Unauthorized copying of this file via any medium
   is strictly prohibited without the written permission
*/

#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

struct edge{
  pair<int, int> vector_comp;
  int edge_length;
  int squ_edge_length;
};

struct coordinate{
  int x ,y;
  vector<edge> connected_vertices;
};


int get_dist(coordinate one, coordinate two)
{
  int dist = sqrt( pow((one.x - two.x),2) + pow((one.y - two.y),2) );
  return dist;
}

int get_squ_dist(coordinate one, coordinate two)
{
  int square_dist = (pow((one.x - two.x),2) + pow((one.y - two.y),2));
  return square_dist;
}


bool is_perpendicular(pair<int, int> vec1, pair<int, int> vec2)
{
  if ( (vec1.first * vec2.first + vec1.second * vec2.second) == 0.0 ) // scalar dot product zero
  {
    return true;
  }
  return false;
}


bool is_square(vector<coordinate> group_of_coords) 
{
  vector<bool> is_square_check_vector;

  if (group_of_coords.size() < 4)
  {
    return false;
  }
  
  for (int i = 0; i < group_of_coords.size(); i++)
  {
    bool perpedicularity_check = false;
    bool diagonal_vector_sameside_check = false;

    // this part is to compute edge lengths and vector components from p1 to other points of the square.
    for (int j = 0; j < group_of_coords.size(); j++)
    {
      if (j != i)
      { // obtain edge length and vector component from coordinate[i] to coordinate[j] and store into connected_vertices
        edge edgecomp;
        
        int edge_length = get_dist(group_of_coords[i], group_of_coords[j]);
        int square_edge_length = get_squ_dist(group_of_coords[i], group_of_coords[j]);        
        edgecomp.edge_length = edge_length;
        edgecomp.squ_edge_length = square_edge_length;
        edgecomp.vector_comp.first = group_of_coords[j].x - group_of_coords[i].x;
        edgecomp.vector_comp.second = group_of_coords[j].y - group_of_coords[i].y;
        group_of_coords[i].connected_vertices.push_back(edgecomp);        
      }
    }
    
    // this is the main part of the check. To check for perpendicularity and the diagonal element of the square being on same side as other two vertices
    for (int k = 0; k < group_of_coords[i].connected_vertices.size(); k++) // connected_vertices size is 3
    {
      for (int l = 0; l < group_of_coords[i].connected_vertices.size(); l++)
      {
        if (l != k && 
            group_of_coords[i].connected_vertices[k].edge_length == group_of_coords[i].connected_vertices[l].edge_length)
        {
          // at this point, we have found two adjacent edges with same length.
          // only thing left to do is to check if the two are perpendicular
          if (perpedicularity_check == true)
          {
            continue;
          }
          perpedicularity_check = is_perpendicular(group_of_coords[i].connected_vertices[k].vector_comp, group_of_coords[i].connected_vertices[l].vector_comp);
        }
        else if (l != k && 
                 2.0*group_of_coords[i].connected_vertices[k].squ_edge_length == group_of_coords[i].connected_vertices[l].squ_edge_length)
        {
          if (diagonal_vector_sameside_check == true){
            continue;
          }

          int conditional_dist = sqrt(pow((group_of_coords[i].connected_vertices[l].vector_comp.first - group_of_coords[i].connected_vertices[k].vector_comp.first),2) +
                                      pow((group_of_coords[i].connected_vertices[l].vector_comp.second - group_of_coords[i].connected_vertices[k].vector_comp.second),2));

          if ( conditional_dist == group_of_coords[i].connected_vertices[k].edge_length)
          {
            diagonal_vector_sameside_check = true;
          }
        } // end of else if
      }

      // Only when both the perpendicularity and diagonal point check to be on the same side are checked we can push "true" to the is_square_check_vector.
      // Move on to the next vertex of the square.
      if (perpedicularity_check == true && diagonal_vector_sameside_check == true)
      {
        is_square_check_vector.push_back(true);
        break;
      }
    }
  }

  cout << "size of check vector: " << is_square_check_vector.size() << endl;
  
  // final condition to check  
  if (is_square_check_vector.size() == 4)
  {
    return true;
  }
  
  return false;
}
  

int main()
{
  vector<coordinate> random_coordinates;
  coordinate coord1, coord2, coord3, coord4;
  
  coord1.x = 1;
  coord1.y = 1;
  
  coord2.x = 3;
  coord2.y = 4;
  
  coord3.x = 4;
  coord3.y = -1;
  
  coord4.x = 6;
  coord4.y = 2;
  
  random_coordinates.push_back(coord1);
  random_coordinates.push_back(coord2);
  random_coordinates.push_back(coord3);
  random_coordinates.push_back(coord4);

  bool is_this_a_square = is_square(random_coordinates);
  
  if (is_this_a_square == true){
    std::cout << "this is a square!!: " << is_this_a_square << std::endl;
  }
  else{
    std::cout << "this is not a square!!: " << is_this_a_square << std::endl;
  }

  return 0;
}



