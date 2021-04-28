import pytest


@pytest.mark.parametrize(
    "test_input,expected",
    [("czy_pierwsza(5)", True), ("czy_pierwsza(2)", True)],
)
def test_eval(test_input, expected):
    assert eval(test_input) == expected


@pytest.mark.parametrize(
    "test_input",
    [(2.5), ("a")],
)
def test_match(test_input):
    with pytest.raises(TypeError, match=r"Błędny typ"):
        czy_pierwsza(test_input)


def czy_pierwsza(n):
    if not isinstance(n, int):
        raise TypeError("Błędny typ")
    else:
        if n == 2:
            return True
        if n % 2 == 0 or n <= 1:
            return False

        pierw = int(n ** 0.5) + 1
        for dzielnik in range(3, pierw, 2):
            if n % dzielnik == 0:
                return False
        return True


print(czy_pierwsza(2))