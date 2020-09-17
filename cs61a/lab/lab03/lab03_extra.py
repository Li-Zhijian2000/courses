""" Optional problems for Lab 3 """

def is_prime(n):
    """Returns True if n is a prime number and False otherwise.

    >>> is_prime(2)
    True
    >>> is_prime(16)
    False
    >>> is_prime(521)
    True
    """
    def f(n, i):
        if n <= i:
            return True
        if n % i == 0:
            return False
        else:
            return f(n, i + 1)
    return f(n, 2)

def gcd(a, b):
    """Returns the greatest common divisor of a and b.
    Should be implemented using recursion.

    >>> gcd(34, 19)
    1
    >>> gcd(39, 91)
    13
    >>> gcd(20, 30)
    10
    >>> gcd(40, 40)
    40
    """
    if a < b:
        return gcd(b, a)
    if a % b == 0:
        return b
    else:
        return gcd(b, a % b)

def ten_pairs(n):
    """Return the number of ten-pairs within positive integer n.

    >>> ten_pairs(7823952)
    3
    >>> ten_pairs(55055)
    6
    >>> ten_pairs(9641469)
    6
    """
    def count(n, d):
        if not n:
            return 0
        if (n % 10 == d):
            return count(n // 10, d) + 1
        else:
            return count(n // 10, d)
    
    if n < 10:
        return 0
    else:
        return ten_pairs(n // 10) + count(n // 10, 10 - n % 10)

