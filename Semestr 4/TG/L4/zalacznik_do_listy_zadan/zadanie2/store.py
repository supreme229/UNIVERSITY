from collections import defaultdict
from tabulate import tabulate


class ProductAlreadyExists(Exception):
    pass


class ProductNotFound(Exception):
    pass


class Store(object):
    def __init__(self, offer=None):
        self.offer = offer if offer else {}

    def add_to_offer(self, product_name, description, price):
        """
        Adds the product to the store's offer.
        :param string product_name:
        :param string description: Product description.
        :param float price: Product price in dollars.
        """
        if product_name in self.offer:
            raise ProductAlreadyExists(
                "Product '{}' is already in the store's offer.".format(product_name)
            )
        self.offer[product_name] = {"description": description, "price": price}

    def delete_from_offer(self, product_name):
        """
        Deletes the product from the store's offer.
        :param string product_name:
        """
        try:
            del self.offer[product_name]
        except KeyError:
            raise ProductNotFound(
                "Product '{}' is not in the store's offer.".format(product_name)
            )

    def update(self, product_name, description=None, price=None):
        """
        Updates information about given product.
        :param string product_name:
        :param string description: New product description.
        :param float price: New product price in dollars.
        """
        try:
            if description is not None:
                self.offer[product_name]["description"] = description
            if price is not None:
                self.offer[product_name]["price"] = price
        except KeyError:
            raise ProductNotFound(
                "Product '{}' is not in the store's offer.".format(product_name)
            )


class Cart(object):
    def __init__(self, store):
        self.store = store
        self.products = defaultdict(int)

    def add(self, product_name, quantity=1):
        if product_name in self.store.offer:
            self.products[product_name] += quantity
        else:
            raise ProductNotFound(
                "Product '{}' is not in the store's offer.".format(product_name)
            )

    def delete(self, product_name):
        if product_name in self.products:
            del self.products[product_name]

    def set_quantity(self, product_name, quantity):
        if product_name in self.products:
            self.products[product_name] = quantity
        else:
            raise ProductNotFound(
                "Product '{}' is not in the shopping cart.".format(product_name)
            )

    def get_total(self):
        return sum(
            self.store.offer[product_name]["price"] * quantity
            for product_name, quantity in self.products.items()
        )

    def show(self):
        if len(self.products) == 0:
            print("Your shopping cart is empty.")
        print("Shopping cart:")
        print(
            tabulate(
                [
                    (product_name, self.store.offer[product_name]["price"], quantity)
                    for product_name, quantity in self.products.items()
                ],
                headers=["Product name", "Price", "Quantity"],
            )
        )
        print("TOTAL: {}".format(self.get_total()))
