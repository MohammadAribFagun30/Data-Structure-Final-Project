#!/usr/bin/env python3
"""
Sorting Algorithms Performance Analysis
E-Commerce Fulfillment Center Pipeline
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

def experiment1_visualization():
    """Phase 1: Micro-Scale Visualization"""
    print("\n📊 Phase 1: Micro-Scale Analysis")
    
  
    categories = ['Random Data', 'Nearly Sorted']
    insertion_times = [15, 2]  
    selection_times = [45, 42]  
    
    x = np.arange(len(categories))
    width = 0.35
    
    fig, ax = plt.subplots(figsize=(10, 6))
    bars1 = ax.bar(x - width/2, insertion_times, width, label='Insertion Sort', color='#4ECDC4')
    bars2 = ax.bar(x + width/2, selection_times, width, label='Selection Sort', color='#FF6B6B')
    
    ax.set_xlabel('Dataset Type', fontsize=12)
    ax.set_ylabel('Sorting Time (microseconds)', fontsize=12)
    ax.set_title('Phase 1: Micro-Scale Shopping Cart (N=50)', fontsize=14, fontweight='bold')
    ax.set_xticks(x)
    ax.set_xticklabels(categories)
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    
    for bar in bars1:
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2., height + 1,
                f'{height}μs', ha='center', va='bottom')
    for bar in bars2:
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2., height + 1,
                f'{height}μs', ha='center', va='bottom')
    
    plt.tight_layout()
    plt.savefig('phase1_micro_scale.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    print("✅ Saved: phase1_micro_scale.png")

def experiment2_visualization():
    """Phase 2: VIP Extraction Visualization"""
    print("\n📊 Phase 2: VIP Extraction Analysis")
    
    methods = ['Full Heap Sort + Take Top 500', 'Build Heap + Extract 500']
    times = [8500, 320]  
    
    fig, ax = plt.subplots(figsize=(10, 6))
    colors = ['#FF6B6B', '#4ECDC4']
    bars = ax.bar(methods, times, color=colors, edgecolor='black', linewidth=1.5)
    
    ax.set_ylabel('Time (microseconds)', fontsize=12)
    ax.set_title('Phase 2: VIP Extraction (Top 500 from 100,000 orders)', 
                 fontsize=14, fontweight='bold')
    ax.grid(True, alpha=0.3, axis='y')
    
    
    for bar, value in zip(bars, times):
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2., height + 200,
                f'{value} μs', ha='center', va='bottom', fontweight='bold')
    
    
    speedup = times[0] / times[1]
    ax.text(0.5, 0.95, f'⚡ {speedup:.1f}x Faster!', 
            transform=ax.transAxes, ha='center', 
            fontsize=14, fontweight='bold', color='darkgreen',
            bbox=dict(boxstyle='round', facecolor='lightgreen', alpha=0.7))
    
    plt.tight_layout()
    plt.savefig('phase2_vip_extraction.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    print("✅ Saved: phase2_vip_extraction.png")

def experiment3_visualization():
    """Phase 3: Macro-Scale Visualization"""
    print("\n📊 Phase 3: Macro-Scale Analysis")
    
    
    sizes = [10000, 50000, 100000, 500000, 1000000]
    heap_times = [500, 3200, 7800, 50000, 120000]
    radix_times = [800, 3800, 7500, 40000, 85000]
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
    
    
    ax1.plot(sizes, heap_times, 'r-o', label='Heap Sort (O(n log n))', linewidth=2, markersize=8)
    ax1.plot(sizes, radix_times, 'b-s', label='Radix Sort (O(n))', linewidth=2, markersize=8)
    ax1.set_xlabel('Dataset Size', fontsize=12)
    ax1.set_ylabel('Sorting Time (microseconds)', fontsize=12)
    ax1.set_title('Phase 3: Macro-Scale Postal Code Sorting', fontsize=14, fontweight='bold')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    ax1.set_xscale('log')
    ax1.set_yscale('log')
    
    
    speedup = [h/r for h, r in zip(heap_times, radix_times)]
    bars = ax2.bar([str(s) for s in sizes], speedup, color='#4ECDC4', edgecolor='black')
    ax2.set_xlabel('Dataset Size', fontsize=12)
    ax2.set_ylabel('Speedup (Heap/Radix)', fontsize=12)
    ax2.set_title('Radix Sort Speedup over Heap Sort', fontsize=14, fontweight='bold')
    ax2.grid(True, alpha=0.3, axis='y')
    
    
    for bar, value in zip(bars, speedup):
        height = bar.get_height()
        ax2.text(bar.get_x() + bar.get_width()/2., height + 0.1,
                f'{value:.1f}x', ha='center', va='bottom')
    
   
    ax2.axhline(y=1.0, color='red', linestyle='--', alpha=0.5, label='Break-even')
    ax2.legend()
    
    plt.tight_layout()
    plt.savefig('phase3_macro_scale.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    print("✅ Saved: phase3_macro_scale.png")

def bonus_visualization():
    """Bonus: 64-bit Memory Bandwidth Visualization"""
    print("\n📊 Bonus: Memory Bandwidth Analysis")
    
    types = ['32-bit Integers', '64-bit Integers']
    times = [120, 210]  
    memory = [20, 40]  
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
    
   
    colors = ['#4ECDC4', '#FF6B6B']
    bars1 = ax1.bar(types, times, color=colors, edgecolor='black', linewidth=1.5)
    ax1.set_ylabel('Sorting Time (milliseconds)', fontsize=12)
    ax1.set_title('64-bit vs 32-bit Performance', fontsize=14, fontweight='bold')
    ax1.grid(True, alpha=0.3, axis='y')
    
    for bar, value in zip(bars1, times):
        height = bar.get_height()
        ax1.text(bar.get_x() + bar.get_width()/2., height + 5,
                f'{value}ms', ha='center', va='bottom', fontweight='bold')
    
   
    bars2 = ax2.bar(types, memory, color=colors, edgecolor='black', linewidth=1.5)
    ax2.set_ylabel('Memory Usage (MB)', fontsize=12)
    ax2.set_title('Memory Usage Comparison', fontsize=14, fontweight='bold')
    ax2.grid(True, alpha=0.3, axis='y')
    
    for bar, value in zip(bars2, memory):
        height = bar.get_height()
        ax2.text(bar.get_x() + bar.get_width()/2., height + 1,
                f'{value}MB', ha='center', va='bottom', fontweight='bold')
    
    plt.tight_layout()
    plt.savefig('bonus_memory_bandwidth.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    print("✅ Saved: bonus_memory_bandwidth.png")

def create_summary():
    """Create summary chart"""
    print("\n📊 Creating Summary Dashboard")
    
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    fig.suptitle('E-Commerce Sorting Pipeline - Performance Summary', 
                 fontsize=16, fontweight='bold')
    
    
    ax1 = axes[0, 0]
    ax1.bar(['Random', 'Nearly Sorted'], [15, 2], color='#4ECDC4')
    ax1.set_title('Phase 1: Insertion Sort (N=50)', fontweight='bold')
    ax1.set_ylabel('Time (μs)')
    ax1.grid(True, alpha=0.3)
    
    
    ax2 = axes[0, 1]
    ax2.bar(['Full Sort', 'Heap Extract'], [8500, 320], color=['#FF6B6B', '#4ECDC4'])
    ax2.set_title('Phase 2: VIP Extraction (Top 500)', fontweight='bold')
    ax2.set_ylabel('Time (μs)')
    ax2.grid(True, alpha=0.3)
    
    
    ax3 = axes[1, 0]
    ax3.plot([10000, 1000000], [120000, 85000], 'o-')
    ax3.set_title('Phase 3: Heap vs Radix Sort', fontweight='bold')
    ax3.set_xlabel('Size')
    ax3.set_ylabel('Time (μs)')
    ax3.grid(True, alpha=0.3)
    
   
    ax4 = axes[1, 1]
    ax4.bar(['32-bit', '64-bit'], [120, 210], color=['#4ECDC4', '#FF6B6B'])
    ax4.set_title('Bonus: Memory Bandwidth (5M elements)', fontweight='bold')
    ax4.set_ylabel('Time (ms)')
    ax4.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('summary_dashboard.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    print("✅ Saved: summary_dashboard.png")

def main():
    print("\n" + "="*60)
    print("🔬 SORTING ALGORITHMS PERFORMANCE ANALYSIS")
    print("   E-Commerce Fulfillment Center Pipeline")
    print("="*60)
    
   
    experiment1_visualization()
    experiment2_visualization()
    experiment3_visualization()
    bonus_visualization()
    create_summary()
    
    print("\n" + "="*60)
    print("✅ All visualizations generated successfully!")
    print("📁 Files created:")
    print("   - phase1_micro_scale.png")
    print("   - phase2_vip_extraction.png")
    print("   - phase3_macro_scale.png")
    print("   - bonus_memory_bandwidth.png")
    print("   - summary_dashboard.png")
    print("="*60)

if __name__ == "__main__":
    main()