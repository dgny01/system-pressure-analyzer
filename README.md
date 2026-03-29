 System Pressure Sentinel (SPS)
A High-Performance Linux Resource Monitoring & Prediction Tool

 Project Overview
SPS is a low-level system monitoring agent written in C++. It focuses on identifying system bottlenecks before they lead to failures (like OOM kills). Unlike traditional monitoring tools that look at "Usage %", SPS leverages Linux PSI (Pressure Stall Information) to understand how much the CPU, Memory, and I/O are actually "stalling" tasks.

Why this project?
Standard monitoring tools (like top or htop) tell you what is happening, but PSI tells you how much it hurts. This tool is designed for SREs and DevOps Engineers who need proactive insights into system health.

 Tech Stack
Language: C++20 (for high-performance data parsing)

Interface: Linux /proc/pressure/ filesystem

Deployment: Dockerized for environment independence

Future Goals: eBPF integration for kernel-level tracing and AI models for OOM prediction.

 Current Features
[x] Real-time PSI Parsing: Efficiently reads and parses avg10, avg60, and avg300 metrics for Memory.

[x] Low Overhead: Designed to run with minimal CPU and memory footprint.

[ ] eBPF Integration: (Coming Soon) Tracking cache misses and context switches.

[ ] Alerting System: Integration with Slack/Webhooks for critical pressure levels.

 Getting Started
Prerequisites
Linux Kernel 4.20+ (with PSI enabled)

CMake & G++

Installation & Run
Bash
git clone https://github.com/dgny01/system-pressure-sentinel.git
cd system-pressure-sentinel
g++ -o sps src/main.cpp
./sps
📈 Roadmap
Phase 1: Solidify C++ parsing and logging (Current).

Phase 2: Containerization with Docker & Prometheus exporting.

Phase 3: eBPF-based kernel event tracking.

Phase 4: Machine Learning model for predictive OOM-Killer prevention.
