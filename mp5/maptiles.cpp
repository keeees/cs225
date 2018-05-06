/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
     std::vector<Point<3>> v;
     std::map<Point<3>,TileImage *> canvastile;

     for(vector<TileImage>::iterator it = theTiles.begin(); it!=theTiles.end(); ++it){
       HSLAPixel temp = it->getAverageColor();

       Point<3> treepoint(((double)temp.h)/360.0, temp.s, temp.l);
       v.push_back(treepoint);

       pair<Point<3>,TileImage*> tempmap(treepoint,&(*it));
       canvastile.insert(tempmap);
     }
     KDTree<3> maptree(v);

    for(int i = 0; i<theSource.getRows(); i++){
      for(int j = 0 ; j<theSource.getColumns();j++){
        HSLAPixel basetemp = theSource.getRegionColor(i,j);
        Point<3> base(((double)basetemp.h)/360.0, basetemp.s, basetemp.l);
        Point<3> tilepoint = maptree.findNearestNeighbor(base);
        canvas->setTile(i,j,canvastile[tilepoint]);
      }
    }

    return canvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
