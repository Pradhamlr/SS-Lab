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
    DBMS_OUTPUT.PUT_LINE(fibonacci_series(&n));
END;



SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE fibonacci_series_proc(n NUMBER)
IS
    a NUMBER := 0;
    b NUMBER := 1;
    c NUMBER;
    i NUMBER;
BEGIN
    IF n >= 1 THEN
        DBMS_OUTPUT.PUT(a || ' ');
    END IF;

    IF n >= 2 THEN
        DBMS_OUTPUT.PUT(b || ' ');
    END IF;

    FOR i IN 3..n LOOP
        c := a + b;
        DBMS_OUTPUT.PUT(c || ' ');
        a := b;
        b := c;
    END LOOP;

    DBMS_OUTPUT.NEW_LINE;
END;
/


BEGIN
    fibonacci_series_proc(&n);
END;
/
