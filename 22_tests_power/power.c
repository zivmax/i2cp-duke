unsigned power(unsigned x, unsigned y)
{
    if (y == 0)
    {
        return 1;
    }
    else if (x == 0)
    {
        return 0;
    }

    return power(x, y - 1) * x;
}
