package AbstractFactory;

class User {
    public int id;
    public String name;
}

interface UserService {
    void insert(User user);
    void getUser(int id);
}

class MysqlUserService implements UserService {
    @Override
    public void insert(User user) {
        System.out.printf("Insert a new user to MySQL database: ID: %d, Name: %s\n", user.id, user.name);
    }

    @Override
    public void getUser(int id) {
        System.out.printf("Search a user in MySQL database: ID %d\n", id);
    }
}

class OracleUserService implements UserService {
    @Override
    public void insert(User user) {
        System.out.printf("Insert a new user to Oracle database: ID: %d, Name: %s\n", user.id, user.name);
    }

    @Override
    public void getUser(int id) {
        System.out.printf("Search a user in Oracle database: ID %d\n", id);
    }
}

public interface DatabaseFactory {
    UserService createUserService();
}

class MysqlFactory implements DatabaseFactory {
    @Override
    public UserService createUserService() {
        return new MysqlUserService();
    }
}

class OracleFactory implements DatabaseFactory {
    @Override
    public UserService createUserService() {
        return new OracleUserService();
    }
}