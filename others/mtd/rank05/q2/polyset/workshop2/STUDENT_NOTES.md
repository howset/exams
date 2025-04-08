# MULTIPLE SUBOBJECTS vs. SINGLE SUBOBJECT in diamond inheritance

Unlike the diamond inheritance scenario in cpp03/ex03 where DiamondTrap should
create the two subobjects so that we may pick-and-choose which method
to inherit from FragTrap and which from ScavTrap...

```C++
DiamondTrap(const DiamondTrap& other) : ScavTrap(other), FragTrap(other)
```

...it appears that in the case of the 'set' class in polyset we actually
want to distinguish between which concrete implementation of the
'searchable_bag' interface we are inheriting from, and accordingly we only create a single subobject.

```C++
set(const searchable_bag& other) {
        if (const searchable_bag *scenarioA = dynamic_cast<const searchable_array_bag*>(&other))
            impl = scenarioA;
        else if (const searchable_bag *scenarioB = dynamic_cast<const searchable_tree_bag*>(&other))
            impl = scenarioB;
        else
            impl = nullptr;
    }
```

Note: dynamic_cast really has nothing to do with diamond inheritance, but rather with the so-called `sub-typing polymorphism`.

# VPTR to a VTABLE of the concrete derived class

```C++
searchable_bag *t = new searchable_tree_bag;
```

When you declare a pointer to a class with virtual functions,
specifically when that function itself is non-instantiable, and you
assign to that pointer a new instance of a concrete derived class,
the compiler ensures that the pointer containts a vptr pointing and
the instance of the concrete derived class that the pointer is pointing
to contains both a vtable with implementations of all virtual functions.
