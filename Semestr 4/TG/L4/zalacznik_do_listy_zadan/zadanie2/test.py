#!python27
import pytest
import store
import random

import json
from collections import defaultdict
import random
import tabulate
import sys


@pytest.fixture
def Store():
    with open("test_offer.json", "r") as file:
        offer = json.loads(file.read())
    return store.Store(offer)


# * TESTOWANIE METOD KLASY STORE

#! Test dla sprawdzenia poprawności dodania elementu do asortymentu sklepu (sprawdzamy, czy jak bedziemy
#! chcieli dodać element już istniejący będzie exception).
#! Korzystamy tutaj z fixtures napisanych powyżej, które wczytało dane z test_offer.
@pytest.mark.store_exception
def test_add_to_offer_1(Store):
    temp_store = Store
    with pytest.raises(store.ProductAlreadyExists):
        temp_store.add_to_offer(
            list(temp_store.offer.keys())[0], "token description", 0
        )


#! Kolejny test dla metody add to offer, tym razem sprawdziłem czy po prostu możemy dodać jakieś
#! inne elementy niż te se test_offer. Dodatkowo w kodzie robię kopię oferty i ręcznie dodaje tam element
#! a następnie sprawdzam czy dostaliśmy taki sam efekt jak po wywołaniu funkcji
@pytest.mark.store_normal
@pytest.mark.parametrize(
    "name, description, price",
    [
        ("Fanta", "Drink1", 4),
        ("Cola", "Drink2", 1),
        ("Cola zero", "Drink3", 2),
        ("Pepsi", "Drink4", 3),
        ("Sprite", "Drink5", 2),
    ],
)
def test_add_to_offer_2(Store, name, description, price):
    temp_store = Store
    offer_copy = Store.offer.copy()
    offer_copy[name] = {"description": description, "price": price}
    temp_store.add_to_offer(name, description, price)
    assert temp_store.offer == offer_copy


#! Test metody delete from offer ze sklepu. Tutaj podaję jakąś całkowicie błedną nazwę produktu i sprawdzam czy
#! wyrzuca wyjątek gdy spróbuje go usunąć.
@pytest.mark.store_exception
def test_delete_from_offer_1(Store):
    temp_store = Store
    name = "Should be exception"
    with pytest.raises(store.ProductNotFound):
        temp_store.delete_from_offer(name)


#! Zwykła próbe usunięcia przedmiotu, który jest dostępny w sklepie. Tworzymy tak jak w add kopię oferty
#! i próbujemy usunąć jeden z elementów
@pytest.mark.store_normal
def test_delete_from_offer_2(Store):
    temp_store = Store
    for i in range(0, 6):
        name = list(Store.offer.keys())[5 - i]
        offer_copy = Store.offer.copy()
        del offer_copy[name]
        temp_store.delete_from_offer(name)
        assert temp_store.offer == offer_copy


#! Test aktualizacji asortymentu sklepu. Generalnie polega na tym, że wszystkie elementy z test_offer zaktualizowałem losowymi danymi.
@pytest.mark.store_normal
@pytest.mark.parametrize(
    "description, price, iter",
    [
        ("Update_1", 1, 0),
        ("Update_2", 32.0, 1),
        ("Update_3", 3, 2),
        ("Update_4", 2.3, 3),
        ("Update_5", None, 4),
        ("Update_6", 0, 5),
    ],
)
def test_update_1(Store, description, price, iter):
    name = list(Store.offer.keys())[iter]
    temp_store = Store
    temp_store.update(name, description, price)
    offer_copy = Store.offer.copy()
    if price is not None:
        offer_copy[name]["price"] = price
    if description is not None:
        offer_copy[name]["description"] = description
    assert temp_store.offer == offer_copy


#! No i tu aktulizujemy produkt, który nie istnieje by sprawdzić czy pojawi się wyjątek
@pytest.mark.store_exception
def test_update_2(Store):
    temp_store = Store
    name = "Should be exception"
    with pytest.raises(store.ProductNotFound):
        temp_store.update(name, 1)


# * TESTOWANIE METOD KLASY CART

#! Okazało się, że na potrzeby przetestowania dalszych metod będę potrzebował 2 fixtures.
#! Jedno zwracające koszyk wypełniony przedmiotami i jedno zwracające pusty.
@pytest.fixture
def Cart_empty(Store):
    return store.Cart(Store)


@pytest.fixture
def Cart_filled(Cart_empty):
    cart = Cart_empty
    for i in Cart_empty.store.offer.keys():
        cart.products[i] = 1
    return cart


#! Pierwsze testujemy dodanie elementu do koszyka, a konkretnie sprawdzamy czy dostaniemy wyjątek gdy będziemy dodać element
#! który nie znajduje sie w sklepie.
@pytest.mark.cart_exception
def test_add_1(Cart_empty):
    test_name = "Should be exception"
    with pytest.raises(store.ProductNotFound):
        Cart_empty.add(test_name, 1)


#! No i dodajemy normalnie elementy
@pytest.mark.skipif(sys.version_info < (4, 0), reason="update to Python4 :O")
@pytest.mark.cart_normal
def test_add_2(Cart_empty):
    temp_cart = Cart_empty
    name = list(Cart_empty.store.offer.keys())[0]
    random_quantity = random.randint(0, 9)
    manual_product = {
        name: random_quantity
    }  # ? potencjalny problem, możemy dodać ile elementów chcemy do koszyka mimo braku dostępności
    temp_cart.add(name, random_quantity)
    assert temp_cart.products == manual_product


#! sprawdzamy czy działa usuwanie, analogicznie jak w sklepie
@pytest.mark.skip
@pytest.mark.cart_normal
def test_delete_1(Cart_filled):
    products_copy = Cart_filled.products.copy()
    name = list(Cart_filled.store.offer.keys())[0]
    del products_copy[name]
    Cart_filled.delete(name)
    assert Cart_filled.products == products_copy


#! Test dla ustalania ilości produktów. Przekazuję losowe liczby do każdego z przedmiotów i sprawadzam rezultaty.
@pytest.mark.skipif(sys.version_info < (3, 8), reason="update to Python3.8")
@pytest.mark.cart_normal
def test_set_quantity_1(Cart_filled):
    for i in range(0, 6):
        random_quantity = random.randint(0, 15)
        products_copy = Cart_filled.products.copy()
        name = list(Cart_filled.products.keys())[i]
        products_copy[name] = random_quantity
        Cart_filled.set_quantity(name, random_quantity)
        assert Cart_filled.products == products_copy


#! I tutaj test dla wyjątków
@pytest.mark.cart_exception
def test_set_quantity_2(Cart_filled):
    name = "Should be exception"
    with pytest.raises(store.ProductNotFound):
        Cart_filled.set_quantity(name, 1)


#! Dodatkowo dla pustego koszyka
@pytest.mark.cart_exception
def test_set_quantity_3(Cart_empty):
    name = "Should be exception"
    with pytest.raises(store.ProductNotFound):
        Cart_empty.set_quantity(name, 1)


#! Test dla sumy kosztów przedmiotów w koszyku. Prosto pętlą zliczamy cena * ilość produktów, która jest dowolną liczbą w danym zakresie
@pytest.mark.cart_normal
def test_get_total_1(Cart_filled):
    sum_cost = 0.0
    for i in Cart_filled.products.keys():
        quantity = random.randint(1, 300)
        Cart_filled.set_quantity(i, quantity)
        sum_cost += Cart_filled.store.offer[i]["price"] * quantity
    assert Cart_filled.get_total() == sum_cost


#! Testy dla pokazywania zawartości koszyka, 1 przypadek - koszyk pusty
@pytest.mark.cart_normal
def test_show_1(Cart_empty, capsys):
    Cart_empty.show()
    real = capsys.readouterr()
    wanted = "Your shopping cart is empty.\n"
    wanted += "Shopping cart:\n"
    wanted += tabulate.tabulate(
        [
            (product_name, Cart_empty.store.offer[product_name]["price"], quantity)
            for product_name, quantity in Cart_empty.products.items()
        ],
        headers=["Product name", "Price", "Quantity"],
    )
    wanted += "\n"
    wanted += "TOTAL: {}".format(0)
    wanted += "\n"
    assert real.out == wanted


#! 2 przypadek - koszyk wypełniony


@pytest.mark.cart_normal
def test_show_2(Cart_filled, capsys):
    Cart_filled.show()
    real = capsys.readouterr()
    wanted = "Shopping cart:\n"
    wanted += tabulate.tabulate(
        [
            (product_name, Cart_filled.store.offer[product_name]["price"], quantity)
            for product_name, quantity in Cart_filled.products.items()
        ],
        headers=["Product name", "Price", "Quantity"],
    )
    wanted += "\n"
    wanted += "TOTAL: {}".format(Cart_filled.get_total())
    wanted += "\n"
    assert real.out == wanted
