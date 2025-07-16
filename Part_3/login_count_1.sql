SELECT COUNT(*) / 7.0 AS avg_logins_per_day
FROM players
WHERE DATE(login_time) BETWEEN DATE('now', '-6 days') AND DATE('now');
