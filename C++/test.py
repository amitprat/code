import kustoclient

# Create a Kusto client
client = kustoclient.KustoClient()

# Create a Kusto query
query = """
SELECT *
FROM KustoDatabase.KustoTable
"""

# Execute the query
results = client.execute_query(query)

# Print the results
for result in results:
  print(result)
