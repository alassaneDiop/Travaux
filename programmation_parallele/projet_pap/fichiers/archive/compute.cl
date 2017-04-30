void cell_stat(__global unsigned *in, __global unsigned *out,int x, int y){
int nb_voisins=0;

  //calcul des voisins


  if (in[(x-1) * DIM + y]!= 0x0) nb_voisins++;
  if (in[(x-1) * DIM + y-1]!= 0x0) nb_voisins++;
  if (in[(x-1) * DIM + y+1]!= 0x0) nb_voisins++;
  if (in[x * DIM + y-1]!= 0x0) nb_voisins++;
  if (in[x * DIM + y+1]!= 0x0)   nb_voisins++;
  if (in[(x+1) * DIM + y-1]!= 0x0) nb_voisins++;
  if (in[(x+1) * DIM + y]!= 0x0) nb_voisins++;
  if (in[(x+1) * DIM + y+1]!= 0x0) nb_voisins++;
  
//cellules vivantes
	out [x * DIM + y]=in[x * DIM + y];
    if (in[x *DIM + y]!= 0x0)
    {
      if (nb_voisins!=2 && nb_voisins!=3) 
     out[x * DIM + y]= 0x0;

    }
    //cellules mortes
    else
    {
      if (nb_voisins==3)out[x * DIM + y]= 0xFFFF00FF;
     
    }

}
__kernel void version_naive (__global unsigned *in, __global unsigned *out)
{
  int x = get_global_id (0);
  int y = get_global_id (1);
  //parcourir cellules
if(x > 0 && x < DIM-1 && y > 0 && y < DIM-1)
	cell_stat(in,out,x,y);
}



__kernel void version_opti (__global unsigned *in, __global unsigned *out)
{
  __local unsigned tile [TILEX][TILEY+1];
  int x = get_global_id (0);
  int y = get_global_id (1);
  int xloc = get_local_id (0);
  int yloc = get_local_id (1);

  tile [xloc][yloc] = in [y * DIM + x];

  barrier (CLK_LOCAL_MEM_FENCE);

  out [(x - xloc + yloc) * DIM + y - yloc + xloc] = tile [yloc][xloc];
}





// NE PAS MODIFIER
static float4 color_scatter (unsigned c)
{
  uchar4 ci;

  ci.s0123 = (*((uchar4 *) &c)).s3210;
  return convert_float4 (ci) / (float4) 255;
}

// NE PAS MODIFIER: ce noyau est appelé lorsqu'une mise à jour de la
// texture de l'image affichée est requise
__kernel void update_texture (__global unsigned *cur, __write_only image2d_t tex)
{
  int y = get_global_id (1);
  int x = get_global_id (0);
  int2 pos = (int2)(x, y);
  unsigned c;

  c = cur [y * DIM + x];

  write_imagef (tex, pos, color_scatter (c));
}
