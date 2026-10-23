// Import the namespace that contains the file-transfer service contracts and classes.
// Without this using directive, the service types below would need their full namespace.
using FileTransferApi.Services;

// Create the application builder.
// The builder reads configuration, prepares logging, and sets up dependency injection.
var builder = WebApplication.CreateBuilder(args);

// Register MVC controllers.
// This tells ASP.NET Core to discover classes such as FileTransferController
// and use their attributes to decide which URLs they handle.
builder.Services.AddControllers();

// Register the HttpClient factory.
// FileTransferService uses this to send HTTP requests from the C# application
// to the C++ application's HTTP server.
builder.Services.AddHttpClient();

// Register the file-transfer service.
// Singleton means one instance is shared for the lifetime of this application.
// The service itself does not keep request-specific state, so sharing is safe here.
builder.Services.AddSingleton<IFileTransferService, FileTransferService>();

// Register the service responsible for listing and opening received files.
// Controllers depend on the interface, while dependency injection supplies this class.
builder.Services.AddSingleton<IReceivedFileService, ReceivedFileService>();

// Build the web application from all of the services and settings above.
var app = builder.Build();

// Map the routes declared by controller attributes such as [HttpPost] and [HttpGet].
app.MapControllers();

// Start Kestrel, the ASP.NET Core web server.
// This call normally keeps the process alive until it is stopped.
app.Run();
