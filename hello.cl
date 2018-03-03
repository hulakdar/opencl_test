__kernel void hello(__global int *buf)
{
    int i = get_global_id(0);

    buf[i] = i;
}
