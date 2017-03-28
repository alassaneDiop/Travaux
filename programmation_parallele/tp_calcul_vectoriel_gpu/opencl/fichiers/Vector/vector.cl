
__kernel void vecmul(__global float *vec,
		     __global float *res,
		     float k)
{
  int index = (get_global_id(0) + 16) % get_local_size(0);

   res[index] = vec[index] * k;
<<<<<<< HEAD
	for (int j=0; j<10;j++)
   		res[index] = vec[index] * k;
=======
>>>>>>> 456a74d9cb87bc071b0bc9a0ac4c884a09aa0bc9
}
