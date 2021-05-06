package zadanie1;

import org.junit.jupiter.api.*;
import org.mockito.*;
import zadanie1.*;
import java.util.*;

public class CarTest{

    @Mock
    private CarDAO carDao = Mockito.mock(CarDAO.class);

    @Mock
    Car carTest1 = new Car();

    @InjectMocks
    CarService carService = new CarService();

    @Test
    public void testFindMileageBetweenYears(){

        carService.setEntityManager(carDao);
        carTest1.setId(1l);
        HashMap<String, Long> hashMap1 = new HashMap<>();

        hashMap1.put("2005", 200l);
        hashMap1.put("2013", 500l);
        hashMap1.put("2018", 300l);
        hashMap1.put("2011", 200l);
        hashMap1.put("2012", 300l);

        carTest1.setYearMileage(hashMap1);
        Mockito.when(carDao.findById(1l)).thenReturn(carTest1);
        Assertions.assertEquals(1500l, carService.findMileageBetweenYears(1l,"2000", "2020"));
    }
}