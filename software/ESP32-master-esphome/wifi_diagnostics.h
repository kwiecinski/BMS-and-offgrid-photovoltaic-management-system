#pragma once

#include <cinttypes>

#include <esp_event.h>
#include <esp_heap_caps.h>
#include <esp_mac.h>
#include <esp_netif.h>
#include <esp_system.h>
#include <esp_timer.h>
#include <esp_wifi.h>

#include "esphome/core/log.h"

namespace wifi_diagnostics {

inline constexpr char TAG[] = "wifi_diag";

inline void log_event(void *, esp_event_base_t base, int32_t event_id, void *data) {
  const int64_t uptime_ms = esp_timer_get_time() / 1000;

  if (base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
    const auto &event = *static_cast<const wifi_event_sta_disconnected_t *>(data);
    ESP_LOGW(TAG, "STA_DISCONNECTED up_ms=%" PRId64 " reason=%u rssi=%d bssid=" MACSTR,
             uptime_ms, static_cast<unsigned>(event.reason), static_cast<int>(event.rssi), MAC2STR(event.bssid));
  } else if (base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED) {
    const auto &event = *static_cast<const wifi_event_sta_connected_t *>(data);
    ESP_LOGI(TAG, "STA_CONNECTED up_ms=%" PRId64 " channel=%u bssid=" MACSTR,
             uptime_ms, static_cast<unsigned>(event.channel), MAC2STR(event.bssid));
  } else if (base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
    const auto &event = *static_cast<const ip_event_got_ip_t *>(data);
    ESP_LOGI(TAG, "STA_GOT_IP up_ms=%" PRId64 " ip=" IPSTR,
             uptime_ms, IP2STR(&event.ip_info.ip));
  } else if (base == IP_EVENT && event_id == IP_EVENT_STA_LOST_IP) {
    ESP_LOGW(TAG, "STA_LOST_IP up_ms=%" PRId64, uptime_ms);
  }
}

inline void setup() {
  const esp_err_t wifi_result = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, log_event, nullptr);
  const esp_err_t ip_result = esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, log_event, nullptr);
  ESP_LOGI(TAG, "BOOT reset_reason=%d idf=%s wifi_events=%s ip_events=%s",
           static_cast<int>(esp_reset_reason()), esp_get_idf_version(),
           esp_err_to_name(wifi_result), esp_err_to_name(ip_result));
}

inline void log_status() {
  constexpr uint32_t heap_caps = MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT;
  const int64_t uptime_ms = esp_timer_get_time() / 1000;
  const unsigned free_heap = heap_caps_get_free_size(heap_caps);
  const unsigned min_heap = heap_caps_get_minimum_free_size(heap_caps);
  const unsigned largest_block = heap_caps_get_largest_free_block(heap_caps);
  wifi_ap_record_t ap{};
  const esp_err_t result = esp_wifi_sta_get_ap_info(&ap);
  if (result == ESP_OK) {
    ESP_LOGI(TAG, "STATUS up_ms=%" PRId64 " sta=associated rssi=%d channel=%u bssid=" MACSTR
                  " heap=%u heap_min=%u heap_largest=%u",
             uptime_ms, static_cast<int>(ap.rssi), static_cast<unsigned>(ap.primary), MAC2STR(ap.bssid),
             free_heap, min_heap, largest_block);
  } else {
    ESP_LOGI(TAG, "STATUS up_ms=%" PRId64 " ap_info=%s heap=%u heap_min=%u heap_largest=%u",
             uptime_ms, esp_err_to_name(result), free_heap, min_heap, largest_block);
  }
}

}  // namespace wifi_diagnostics
