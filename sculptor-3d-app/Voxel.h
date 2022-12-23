#ifndef VOXEL_H
#define VOXEL_H
/**
 *  @brief Struct Voxel representa as propriedades de um voxel
 *  @details No struct definimos a cor dos voxel no formato rgba ese está ativado ou não
 */

struct Voxel {
  float r,g,b; // Colors
  float a; // Transparency
  bool isOn; // Included or not
};

#endif // VOXEL_H
