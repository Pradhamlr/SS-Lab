SET SERVEROUTPUT ON;

CREATE OR REPLACE FUNCTION fibonacci_series(n NUMBER)
RETURN VARCHAR2
IS
    a NUMBER := 0;
    b NUMBER := 1;
    c NUMBER;
    i NUMBER;
    result VARCHAR2(1000) := '';
BEGIN
    IF n >= 1 THEN
        result := result || a || ' ';
    END IF;

    IF n >= 2 THEN
        result := result || b || ' ';
    END IF;

    FOR i IN 3..n LOOP
        c := a + b;
        result := result || c || ' ';
        a := b;
        b := c;
    END LOOP;

    RETURN result;
END;
/


BEGIN
    DBMS_OUTPUT.PUT_LINE('Fibonacci Series: ' || fibonacci_series(&n));
END;
/


SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE fibonacci_series(limit NUMBER)
IS
    a NUMBER := 0;
    b NUMBER := 1;
    c NUMBER;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Fibonacci Series up to ' || limit || ':');
    DBMS_OUTPUT.PUT(a || ' ' || b || ' ');

    LOOP
        c := a + b;
        EXIT WHEN c > limit;
        DBMS_OUTPUT.PUT(c || ' ');
        a := b;
        b := c;
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;
/
