use actix_web::{web, App, HttpServer, Responder};
use chrono::Local;

async fn index() -> impl Responder {
    let now = Local::now();
    let os_type = sys_info::os_type().unwrap_or_else(|_| "Onbekend".to_string());
    let os_release = sys_info::os_release().unwrap_or_else(|_| "Onbekend".to_string());
    let mem_info = sys_info::mem_info().unwrap_or(sys_info::MemInfo {
        total: 0,
        free: 0,
        avail: 0,
        buffers: 0,
        cached: 0,
        swap_free: 0,
        swap_total: 0,
    });

    format!(
        "Het is nu {}\n\n\nOS: {} {}\n\nTotale geheugen: {} MB\nVrij geheugen: {} MB",
        now.format("%Y-%m-%d %H:%M:%S"),
        os_type,
        os_release,
        mem_info.total / 1024,
        mem_info.free / 1024
    )
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| App::new().route("/", web::get().to(index)))
        .bind("0.0.0.0:8080")?
        .run()
        .await
}
