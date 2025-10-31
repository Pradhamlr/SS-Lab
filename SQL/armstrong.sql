SET SERVEROUTPUT ON;

CREATE OR REPLACE FUNCTION is_armstrong(n NUMBER)
RETURN VARCHAR2
IS
    temp NUMBER := n;
    rem NUMBER;
    sum NUMBER := 0;
    digits NUMBER := 0;
BEGIN

    WHILE temp > 0 LOOP
        digits := digits + 1;
        temp := FLOOR(temp / 10);
    END LOOP;

    temp := n;

    WHILE temp > 0 LOOP
        rem := MOD(temp, 10);
        sum := sum + POWER(rem, digits);
        temp := FLOOR(temp / 10);
    END LOOP;

    IF sum = n THEN
        RETURN n || ' is an ARMSTRONG number.';
    ELSE
        RETURN n || ' is NOT an ARMSTRONG number.';
    END IF;
END;
/



SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE check_armstrong(n NUMBER)
IS
    num NUMBER := n;
    rem NUMBER;
    sum NUMBER := 0;
    digits NUMBER := LENGTH(TO_CHAR(n));
BEGIN
    WHILE num > 0 LOOP
        rem := MOD(num, 10);
        sum := sum + POWER(rem, digits);
        num := TRUNC(num / 10);
    END LOOP;

    IF sum = n THEN
        DBMS_OUTPUT.PUT_LINE(n || ' is an ARMSTRONG number.');
    ELSE
        DBMS_OUTPUT.PUT_LINE(n || ' is NOT an ARMSTRONG number.');
    END IF;
END;
/
