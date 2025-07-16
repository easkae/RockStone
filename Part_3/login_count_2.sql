SELECT COUNT(*) / 7.0 AS avg_logins_per_day
FROM players
WHERE DATE(login_time) BETWEEN DATE('now', '-7 days') AND DATE('now', '-1 day');
