# 2023

1. Creational
Factory Method: there are different types of sensors and devices; a factory method for each of them can help in the creation of these objects,  making it easier to expand the smart home with new types of sensors and devices.

2. Structural Design Patterns
- Adapter: Since the app reads the smart home's current state from and to a file, it could be useful to have an adaper that could convert the data to and from a specific format. This way we could use our data with other smart home management applications or other useful features that wouldn't work with the application's specific format.

- Decorator: Since the app has sensors and devices of different types, a decorator could be a useful way to specify the types of these. There can be a lot of situations that can appear, so a decorator pattern will be perfect for this because you can combine several behaviors by wrapping an object into multiple decorators.

3. Behavioral Design Patterns
- Memento: The application allows users to add or delete entities, therefor it should allow them to undo these actions too. Memento would be perfect to restore the previous state of the smart home, it could be very useful.
	
- Observer: The observer pattern can be very useful in the context of multiple concurent clients that acces the same resurse. Also, you can introduce new subscriber classes without having to change the original code, so if a new device is added, it can easily monitor the other sensors.