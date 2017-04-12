
__kernel void transpose (__global unsigned *in, __global unsigned *out)
{
  int y = get_global_id (1);
  int x = get_global_id (0);
  unsigned couleur;

 // couleur = in [y * DIM + x];
  couleur = in [y * DIM + x];

 // y = (y ? y - 1 : get_global_size (1) - 1);

 // out [y * DIM + x] = couleur;
  out [x * DIM + y] = couleur;
}


// NE PAS MODIFIER: ce noyau est appelé lorsqu'une mise à jour de la
// texture de l'image affichée est requise
__kernel void update_texture (__global unsigned *cur, __write_only image2d_t tex)
{
  int y = get_global_id (1);
  int x = get_global_id (0);
  int2 pos = (int2)(x, y);
  unsigned c;
  float4 couleur;

  c = cur [y * DIM + x];

  couleur.w = (c & 0xFF) / (0xFF * 1.0);
  couleur.z = (c & 0xFF00) / (0xFF00 * 1.0);
  couleur.y = (c & 0xFF0000) / (0xFF0000 * 1.0);
  couleur.x = (c & 0xFF000000) / (0xFF000000 * 1.0);

  write_imagef (tex, pos, couleur);
}

