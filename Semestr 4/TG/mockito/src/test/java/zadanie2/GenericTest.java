package zadanie2;

import org.junit.jupiter.api.*;
import org.mockito.*;
import zadanie2.*;
import java.util.*;
import java.io.*;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.junit.jupiter.MockitoExtension;

@ExtendWith(MockitoExtension.class)
public class GenericTest{

    @InjectMocks
    GenericDAO genericDao =  new GenericDAO();
    
    @Mock
    private Session session = Mockito.mock(Session.class);
    
    @Mock
    private DbLogger dbLogger = Mockito.mock(DbLogger.class);
    
    Object object = new Object();
    @Test
    public void testSave1() throws SessionOpenException{
        genericDao.setSession(session);
        Mockito.doThrow(SessionOpenException.class).when(session).open();
        Assertions.assertThrows(SessionOpenException.class, () -> genericDao.save(object));
    }
    @Captor
    private ArgumentCaptor<Exception> exceptionCaptor;

    @Test
    public void testSave2() throws SessionOpenException, CommitException{
        genericDao.setDbLogger(dbLogger);
        genericDao.setSession(session);
        Mockito.doThrow(CommitException.class).when(session).commitTransaction();
        genericDao.save(object);
        Mockito.verify(dbLogger).log(exceptionCaptor.capture());
        Assertions.assertTrue(exceptionCaptor.getAllValues().stream().findFirst().get() instanceof CommitException);
    }
}