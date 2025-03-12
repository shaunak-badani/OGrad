import sqlite3

JOBS_SCHEMA = """
CREATE TABLE IF NOT EXISTS jobs(taskid, pid, totalSteps)
"""


class DBHelper:

    def initialize_database():
        con = sqlite3.connect("jobs.db")
        con.execute(JOBS_SCHEMA)
        print("Created jobs table!")

    def get_db_object():
        return sqlite3.connect("jobs.db")

    @staticmethod
    def execute_query(query, params = None):
        con = DBHelper.get_db_object()
        cur = con.cursor()
        if params:
            results = cur.execute(query, params)
        else:
            results = cur.execute(query)
        con.commit()
        all_results = list(results)
        cur.close()
        return all_results
        